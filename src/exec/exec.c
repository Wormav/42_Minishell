/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/04 15:29:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static long	execute_child_process(char *cmd_name, char **argv_cmd,
char **env_lst, t_cmd *cmd)
{
	if (!cmd_name)
	{
		if (execve(cmd->cmd, argv_cmd, env_lst) == -1)
		{
			ft_putendl_fd(ft_strsjoin(3, "bash: ", cmd->cmd,
					": command not found"), 2);
			return (127);
		}
	}
	if (execve(cmd_name, argv_cmd, env_lst) == -1)
	{
		ft_putendl_fd(ft_strsjoin(3, "bash: ", cmd_name,
				": command not found"), 2);
		return (127);
	}
	return (0);
}

static void	process_others_cmd(t_cmd *cmd, t_env **env_lst, long *error)
{
	char	**test_env;
	char	*cmd_name;
	char	**argv_cmd;
	pid_t	pid;
	int		status;

	test_env = env_tab(*env_lst);
	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		cmd_name = cmd->cmd;
	else
		cmd_name = find_cmd(cmd, *env_lst, error);
	argv_cmd = join_params(cmd);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		*error = execute_child_process(cmd_name, argv_cmd, test_env, cmd);
		if (*error == 127)
			exit(127);
	}
	waitpid(pid, &status, 0);
	*error = WEXITSTATUS(status);
}

static void	exec_cmd(t_cmd *cmd, long *error, t_env **env_lst, int *flag_exit)
{
	char	*save_return;

	save_return = ft_strsjoin(3, "?=\"", ft_ltoa(*error), "\"");
	env_list_insert(env_lst, env_lstnew(save_return));
	if (cmd->params)
		cmd_filter_params(&cmd);
	if (!ft_strcmp(cmd->cmd, "echo"))
		execute_echo(cmd, *env_lst);
	*error = 0;
	if (!ft_strcmp(cmd->cmd, "pwd"))
		execute_pwd(cmd, error);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		execute_unset(cmd, error, env_lst);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		execute_cd(*env_lst, cmd, error);
	else if (!ft_strcmp(cmd->cmd, "export"))
		execute_export(env_lst, cmd, error);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		execute_exit(cmd, error, flag_exit);
	else if (!ft_strcmp(cmd->cmd, "env"))
		execute_env(*env_lst, cmd, error);
	else if (ft_strcmp(cmd->cmd, "echo"))
		process_others_cmd(cmd, env_lst, error);
}

void	exec(t_ast *ast, t_env **env_lst, int *flag_exit)
{
	t_cmd		*cmd;
	static long	error = 0;

	ast->content = ft_strtrim(ast->content, " ");
	cmd = NULL;
	cmd = exec_create_cmd(ast->content);
	trim_cmd_and_options(cmd);
	exec_cmd(cmd, &error, env_lst, flag_exit);
	cleanup_cmd(cmd);
}
