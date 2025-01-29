/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/29 11:24:53 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *process_env_var_sq(t_env *env, char *result, char *var_start)
{
	char *quote_start;
	char *quote_end;

	if (*(var_start + 1) == '=' || *(var_start + 1) == '+')
		return result;

	quote_start = ft_strchr(result, '\'');
	while (quote_start && quote_start < var_start)
	{
		quote_end = ft_strchr(quote_start + 1, '\'');
		if (!quote_end)
			return process_env_var(env, result, var_start);
		if (var_start > quote_start && var_start < quote_end)
			return result;
		quote_start = ft_strchr(quote_end + 1, '\'');
	}
	return process_env_var(env, result, var_start);
}

char *env_replace_env_vars_sq(t_env *env, char *str)
{
	char *result;
	char *var_start;
	char *prev_result;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	var_start = ft_strchr(result, '$');
	while (var_start)
	{
		prev_result = ft_strdup(result);
		result = process_env_var_sq(env, result, var_start);
		var_start = ft_strchr(result, '$');
		if (ft_strcmp(prev_result, result) == 0)
			break;
		lp_free(prev_result);
	}
	return (result);
}

int check_dollar_sign(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int check_option_n(char *str)
{
	int i;

	if (!str || str[0] != '-' || !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int count_option_n(char **options)
{
	int count;
	int i;

	if (!options)
		return (0);
	count = 0;
	i = 0;
	while (options[i] && check_option_n(options[i]))
	{
		count++;
		i++;
	}
	return (count);
}

void process_with_dollar(char *str, t_env *env)
{
	char *replace_env;
	char *filter_quotes;
	char *trim;

	replace_env = env_replace_env_vars_sq(env, str);
	filter_quotes = parser_filter_quote(replace_env);
	trim = ft_strtrim(filter_quotes, " ");
	printf("%s", trim);
}

void ft_echo(t_cmd *cmd, int *error, t_env *env)
{
	(void)error;
	int count_n;
	int i;

	i = count_option_n(cmd->options);
	count_n = i;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			if (ft_strcmp(cmd->options[i],"-n") || i != 0)
				printf("%s ", cmd->options[i]);
			i++;
		}
	}
	if (!check_dollar_sign(cmd->params))
		printf("%s",ft_strtrim(parser_filter_quote(cmd->params), " "));
	else
		process_with_dollar(cmd->params, env);
	if (count_n)
		return ;
	printf("\n");
}
