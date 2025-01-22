/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:41:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// !retirer les prints

static void	trim_cmd_and_options(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		tmp = ft_strtrim(cmd->cmd, " '\"\t");
		lp_free(cmd->cmd);
		cmd->cmd = tmp;
	}
	if (cmd->options)
	{
		i = 0;
		while (cmd->options[i])
		{
			tmp = ft_strtrim(cmd->options[i], " '\"\t");
			lp_free(cmd->options[i]);
			cmd->options[i] = tmp;
			i++;
		}
	}
}

static char	*exec_cmd(t_cmd *cmd, int *error, t_env *env_lst)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(cmd->cmd, "pwd"))
		result = execute_pwd(cmd, error);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		result = execute_unset(cmd, error, env_lst);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(env_lst, cmd, error);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(&env_lst, cmd, error);
	return (result);
}

void	exec(t_ast *ast, t_env *env_lst)
{
	t_cmd	*cmd;
	t_fds	*fds;
	char	*fd;
	char	*result;
	int		error;

	error = 0;
	cmd = NULL;
	fds = NULL;
	fd = exec_identify_fd(ast);
	exec_store_other_fds(ast, &fds, fd);
	print_fds(fds);
	printf("FD =======> [%s]\n", fd);
	cmd = exec_create_cmd(ast->content);
	trim_cmd_and_options(cmd);
	print_cmd(cmd);
	result = exec_cmd(cmd, &error, env_lst);
	if (error)
	{
		ft_putendl_fd("Error !!!!", 2);
		ft_putendl_fd(result, 2);
	}
	else
		printf("%s", result);
	lp_free(result);
	cleanup_cmd(cmd);
	exec_free_fds(fds);
}
