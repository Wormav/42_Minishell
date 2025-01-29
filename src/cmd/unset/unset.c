/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:46 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 15:31:42 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*handle_bang_error(char *param, long *error)
{
	char	*error_message;
	char	*after_bang;
	int		i;

	i = 0;
	while (param[i] && param[i] != '!')
		i++;
	if (param[i] == '!' && param[i + 1] != '\0')
	{
		after_bang = ft_strdup(param + i);
		if (!after_bang)
			return (NULL);
		error_message = ft_strjoin("bash: ", after_bang);
		lp_free(after_bang);
		if (!error_message)
			return (NULL);
		after_bang = ft_strjoin(error_message, ": event not found\n");
		lp_free(error_message);
		*error = 1;
		return (after_bang);
	}
	return (NULL);
}

static void	process_unset_params(char **params, t_env *env_lst)
{
	int	i;

	i = 0;
	while (params[i])
	{
		if (params[i][0] == '$')
			env_list_remove(&env_lst, env_get_value(env_lst, params[i]));
		else
			env_list_remove(&env_lst, params[i]);
		i++;
	}
}

static char	*check_unset_params(char **params, long *error)
{
	char	*result;
	int		i;

	i = 0;
	while (params[i])
	{
		result = handle_bang_error(params[i], error);
		if (result)
		{
			*error = 2;
			free_split(params);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*execute_unset(t_cmd *cmd, long *error, t_env *env_lst)
{
	char	*result;
	char	**params;

	if (cmd->options)
	{
		*error = 2;
		return (handle_bad_option(cmd->options[0], "unset"));
	}
	params = ft_split(cmd->params, ' ');
	if (!params)
		return (NULL);
	result = check_unset_params(params, error);
	if (result)
		return (result);
	process_unset_params(params, env_lst);
	free_split(params);
	return (NULL);
}
