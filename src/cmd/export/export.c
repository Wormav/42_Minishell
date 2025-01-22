/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 18:34:53 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
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

void	process_args(char *split, int *error, t_envp **env)
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
		env_list_insert(env, env_lstnew(tmp));
	}
	else
		env_list_insert(env, env_lstnew(split));
}

void	process_params(t_envp **env, t_cmd *cmd, int *error)
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

void	ft_export(t_envp **env, t_cmd *cmd, int *error)
{
	if (!*(cmd->params) && !cmd->options)
	{
		env_print(*env);
		return ;
	}
	process_params(env, cmd, error);
}
