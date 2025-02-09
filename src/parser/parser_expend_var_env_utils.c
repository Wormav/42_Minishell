/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expend_var_env_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:18:19 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 22:23:20 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser_check_dollar_sign(char *str)
{
	int	i;
	int	in_quotes;

	if (!str)
		return (0);
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		if (str[i] == '$' && !in_quotes)
		{
			if (str[i + 1] == '?')
				return (2);
			if (ft_isalnum(str[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*parser_process_status_exit(char *result, char *var_start, t_env *env)
{
	char	*new_result;
	char	*exit_str;
	int		len;
	int		total_len;

	exit_str = env_get_value(env, "$?");
	if (!exit_str)
		return (result);
	len = var_start - result;
	total_len = len + ft_strlen(exit_str) + ft_strlen(var_start + 2) + 1;
	new_result = lp_alloc(total_len * sizeof(char));
	if (!new_result)
		return (result);
	ft_strlcpy(new_result, result, len + 1);
	ft_strlcat(new_result, exit_str, total_len);
	ft_strlcat(new_result, var_start + 2, total_len);
	lp_free(result);
	return (new_result);
}
