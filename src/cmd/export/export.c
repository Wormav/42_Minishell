/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/21 16:01:34 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "env.h"
#include "exec.h"
#include "utils.h"
#include <minishell.h>

int	check_bad_params(char *str)
{
	if (*str == '-')
		return (1);
	return (!ft_isalpha(*str));
}

int	find_next_sign(char sign, char *str)
{
	char	*start;

	start = str;
	str++;
	while (*str && *str != sign)
		str++;
	return (str - start);
}

void	process_args(char *split, int *error, t_list **env)
{
	char	*tmp = NULL;
	char	**split_equal;

	if (!ft_isalpha(*split))
	{
		*error = 1;
		return ;
	}
	if (find_next_sign('=', split) != (int)ft_strlen(split))
	{
		split_equal = ft_split(split, '=');
		tmp = ft_strsjoin(5, split_equal[0], "=", "\"", split_equal[1], "\"");
		free_split(split_equal);
	}
	env_list_insert(env, ft_lstnew(tmp));
}

void	process_params(t_list **env, t_cmd *cmd, int *error)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(cmd->params, ' ');
	while (split[i])
	{
		process_args(split[i], error, env);
		if (*error)
		{
			free_split(split);
			return ;
		}
		i++;
	}
}

void	ft_export(t_list **env, t_cmd *cmd, int *error)
{
	if (!*(cmd->params) && !cmd->options)
	{
		env_print(*env);
		return ;
	}
	process_params(env, cmd, error);
}
