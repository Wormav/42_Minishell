/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:37:41 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 09:29:08 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(t_list *env, t_cmd *cmd, int *error)
{
	if (access(cmd->params, 0) == F_OK)
	{
		env_list_insert(&env,
			ft_lstnew(ft_strsjoin(2, "OLDPDW", execute_pwd(cmd, error))));
		chdir(cmd->params);
		env_list_insert(&env, ft_lstnew(ft_strsjoin(2, "PWD=", cmd->params)));
	}
	else
		printf("Minishell: %s not a directory\n", cmd->params);
}
