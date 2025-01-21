/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/21 13:08:55 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "env.h"
#include "exec.h"
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

void	process_args(char **split_space, int *error, t_list **env)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	while (split_space[i])
	{
		j = 0;
		split = ft_split(split_space[i], '=');
		while (split[0][j] && ft_isascii(split[0][j]))
			j++;
		if (split[0][j])
		{
			*error = 1;
			return ;
		}	
		split[1] = ft_strtrim(split[1], "'\"");
		char *str = ft_strsjoin(5, split[0], "=", "\"", split[1], "\"");
		str = ft_strtrim(str, " ");
		env_list_insert(env, ft_lstnew(str));
		i++;
	}
}

void	process_params(t_list **env, t_cmd *cmd, int *error)
{
	char	**split;

	split = ft_split(cmd->params, ' ');
	process_args(split, error, env);
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
