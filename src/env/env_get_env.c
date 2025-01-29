/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:54:43 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 08:37:07 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*process_env_value(char *content, int keylen)
{
	char	*value;
	int		len;

	value = content + keylen + 1;
	if (*value == '"')
	{
		value++;
		len = ft_strlen(value);
		if (len > 0 && value[len - 1] == '"')
			value[len - 1] = '\0';
	}
	len = ft_strlen(value);
	if (len > 0 && value[len - 1] == '\n')
		value[len - 1] = '\0';
	return (value);
}

char	*env_get_value(t_env *env, char *key)
{
	t_env	*tmp;
	int		keylen;
	char	*content;

	if (!key || !env || key[0] != '$')
		return (NULL);
	key++;
	keylen = ft_strlen(key);
	tmp = env;
	while (tmp)
	{
		content = tmp->content;
		if (ft_strncmp(content, "declare -x ", 11) == 0)
			content += 11;
		if (!ft_strncmp(content, key, keylen)
			&& ((char *)content)[keylen] == '=')
			return (process_env_value(content, keylen));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*process_env_var(t_env *env, char *result, char *var_start)
{
	char	*var_end;
	char	*var_value;
	char	*tmp;
	char	*new_result;
	int		i;

	var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	i = var_end - var_start;
	tmp = ft_substr(var_start, 0, i);
	var_value = env_get_value(env, tmp);
	lp_free(tmp);
	if (!var_value)
		var_value = "";
	tmp = ft_substr(result, 0, var_start - result);
	new_result = ft_strjoin(tmp, var_value);
	lp_free(tmp);
	tmp = new_result;
	new_result = ft_strjoin(tmp, var_end);
	lp_free(tmp);
	lp_free(result);
	return (new_result);
}

char	*env_replace_env_vars(t_env *env, char *str)
{
	char	*result;
	char	*var_start;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	var_start = ft_strchr(result, '$');
	while (var_start)
	{
		result = process_env_var(env, result, var_start);
		var_start = ft_strchr(result, '$');
	}
	return (result);
}

int	env_has_env_vars(char *str)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*str == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*str == '$' && !in_single_quote)
			return (1);
		str++;
	}
	return (0);
}
