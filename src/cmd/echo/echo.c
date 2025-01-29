/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/29 18:28:16 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*process_env_var_sq(t_env *env, char *result, char *var_start)
{
	char	*quote_start;
	char	*quote_end;

	if (*(var_start + 1) == '=' || *(var_start + 1) == '+')
		return (result);
	quote_start = ft_strchr(result, '\'');
	while (quote_start && quote_start < var_start)
	{
		quote_end = ft_strchr(quote_start + 1, '\'');
		if (!quote_end)
			return (process_env_var(env, result, var_start));
		if (var_start > quote_start && var_start < quote_end)
			return (result);
		quote_start = ft_strchr(quote_end + 1, '\'');
	}
	return (process_env_var(env, result, var_start));
}

static char	*process_env_vars_loop(t_env *env, char *result, char **pos)
{
	char	*prev_result;
	int		in_quotes;

	in_quotes = 0;
	while (**pos)
	{
		if (**pos == '\'')
			in_quotes = !in_quotes;
		else if (**pos == '$' && !in_quotes)
		{
			prev_result = ft_strdup(result);
			result = process_env_var_sq(env, result, *pos);
			if (ft_strcmp(prev_result, result) == 0)
			{
				lp_free(prev_result);
				break ;
			}
			lp_free(prev_result);
			*pos = result;
			continue ;
		}
		(*pos)++;
	}
	return (result);
}

char	*env_replace_env_vars_sq(t_env *env, char *str)
{
	char	*result;
	char	*pos;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	pos = result;
	return (process_env_vars_loop(env, result, &pos));
}

void	process_with_dollar(char *str, t_env *env)
{
	char	*replace_env;
	char	*filter_quotes;
	char	*trim;

	replace_env = env_replace_env_vars_sq(env, str);
	filter_quotes = parser_filter_quote(replace_env);
	trim = ft_strtrim(filter_quotes, " ");
	printf("%s", trim);
}

void	ft_echo(t_cmd *cmd, t_env *env)
{
	int	count_n;
	int	i;

	i = echo_count_option_n(cmd->options);
	count_n = i;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			if (ft_strcmp(cmd->options[i], "-n") || i != 0)
				printf("%s ", cmd->options[i]);
			i++;
		}
	}
	if (!echo_check_dollar_sign(cmd->params))
		printf("%s", ft_strtrim(parser_filter_quote(cmd->params), " "));
	else
		process_with_dollar(cmd->params, env);
	if (count_n)
		return ;
	printf("\n");
}
