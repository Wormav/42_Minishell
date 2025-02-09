/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:46 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 22:30:43 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*handle_bang_error(char *param, t_data *data)
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
		data->error = 1;
		return (after_bang);
	}
	return (NULL);
}

static void	process_unset_params(char **params, t_env **env_lst)
{
	int	i;

	i = 0;
	while (params[i])
	{
		env_list_remove(env_lst, params[i]);
		i++;
	}
}

static char	*check_unset_params(char **params, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	while (params[i])
	{
		result = handle_bang_error(params[i], data);
		if (result)
		{
			data->error = 2;
			free_split(params);
			return (result);
		}
		i++;
	}
	return (NULL);
}

void	execute_unset(t_cmd *cmd, t_data *data, t_env **env_lst)
{
	char	*result;
	char	**params;

	if (cmd->options)
	{
		data->error = 2;
		printf("%s\n", handle_bad_option(cmd->options[0], "unset"));
		return ;
	}
	params = ft_split(cmd->params, ' ');
	if (!params)
		return ;
	result = check_unset_params(params, data);
	if (result)
		return ;
	process_unset_params(params, env_lst);
	free_split(params);
	return ;
}
