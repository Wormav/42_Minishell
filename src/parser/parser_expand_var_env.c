/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_var_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:57:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 18:36:49 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int handle_exit_status(char *result, int *j, t_env *env)
{
	char *exit_value;

	exit_value = env_get_value(env, "$?");
	if (exit_value)
	{
		size_t len = ft_strlen(exit_value);
		ft_strlcat(result, exit_value, *j + len + 1);
		*j += len;
	}
	return 2;
}

static int handle_env_var(char *str, char *result, int *j, t_env *env)
{
    int var_len = 0;
    char *var_name;
    char *value;

    str++;
    while (str[var_len] && (isalnum(str[var_len]) || str[var_len] == '_'))
        var_len++;
    var_name = ft_substr(str, 0, var_len);
    if (!var_name)
        return 1;
    char *search_key = ft_strjoin("$", var_name);
    value = env_get_value(env, search_key);
    lp_free(var_name);
    lp_free(search_key);
    if (value)
    {
        size_t len = ft_strlen(value);
        ft_strlcat(result, value, *j + len + 1);
        *j += len;
    }
    return var_len + 1;
}

static char *init_expansion(char *str)
{
	char *result;

	result = lp_alloc((strlen(str) * 4 + 1) * sizeof(char));
	if (!result)
		return NULL;
	return result;
}

static void process_var_expansion(char *str, char *result, int *i, int *j, t_env *env, int in_single_quotes)
{
	if (!in_single_quotes && str[*i] == '$')
	{
		if (str[*i + 1] == '?')
			*i += handle_exit_status(result, j, env);
		else if (isalnum(str[*i + 1]) || str[*i + 1] == '_')
			*i += handle_env_var(str + *i, result, j, env);
		else
			result[(*j)++] = str[(*i)++];
	}
	else
		result[(*j)++] = str[(*i)++];
}

void parser_expand_var_env(t_data *data, t_env *env)
{
	char *result;
	int i;
	int j;
	int in_single_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	if (!data->str_prompt)
		return;
	if (!(result = init_expansion(data->str_prompt)))
		return;
	while (data->str_prompt[i])
	{
		if (data->str_prompt[i] == '\'')
			in_single_quotes = !in_single_quotes;
		process_var_expansion(data->str_prompt, result, &i, &j, env, in_single_quotes);
	}
	result[j] = '\0';
	lp_free(data->str_prompt);
	data->str_prompt = result;
}
