/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_var_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:57:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 22:23:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *process_env_var_sq(t_env *env, char *result, char *var_start)
{
    char *quote_start;
    char *quote_end;
    char next_char;

    next_char = *(var_start + 1);
    if (next_char == '\0' || next_char == ' ' || next_char == '$')
        return (result);
    if (next_char == '=' || next_char == '+')
        return (result);
    if (next_char == '?')
        return (parser_process_status_exit(result, var_start, env));
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

static char *process_env_vars_loop(t_env *env, char *result, char **pos)
{
	char *prev_result;
	int in_quotes;

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
				break;
			}
			lp_free(prev_result);
			*pos = result;
			continue;
		}
		(*pos)++;
	}
	return (result);
}

static char *env_replace_env_vars_sq(t_env *env, char *str)
{
	char *result;
	char *pos;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	pos = result;
	return (process_env_vars_loop(env, result, &pos));
}

void parser_expand_var_env(t_data *data, t_env *env)
{
	char *expanded;

	if (!data->str_prompt)
		return;
	if (!parser_check_dollar_sign(data->str_prompt))
		return;
	expanded = env_replace_env_vars_sq(env, data->str_prompt);
	if (expanded)
	{
		lp_free(data->str_prompt);
		data->str_prompt = expanded;
	}
}
