/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:47:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/18 11:49:23 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**exec_path_parsing(t_env *env, long *error)
{
	char	**split;

	while (env && ft_strncmp(env->content, "PATH=", 5))
		env = env->next;
	if (!env)
	{
		*error = 1;
		return (NULL);
	}
	split = ft_split(env->content, ':');
	return (split);
}

char	*find_cmd(t_cmd *cmd, t_env *env, long *error)
{
	char	**paths;
	char	*tmp_path;
	int		i;

	paths = exec_path_parsing(env, error);
	if (*error)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strsjoin(3, paths[i], "/", cmd->cmd);
		if (access(&tmp_path[4], F_OK) == 0 && access(&tmp_path[4], X_OK) == 0)
		{
			free_split(paths);
			return (tmp_path);
		}
		lp_free(tmp_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
