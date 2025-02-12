/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/12 17:37:56 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
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

static void	execute_child_process(char *cmd_name, char **argv_cmd,
char **env_lst, t_cmd *cmd)
{
	cmd->cmd = ft_strtrim(cmd->cmd, "\t ");
	if ((!ft_strncmp(cmd->cmd, "./", 2) || *(cmd->cmd) == '/'))
	{
		if (is_directory(cmd->cmd))
		{
			ft_printf(2, "minishell: %s: Is a directory\n", cmd->cmd);
				exit(126);
		}
		else if (access(cmd->cmd, F_OK) != 0)
		{
			ft_printf(2, "minishell: %s: No such file or directory\n", cmd->cmd);
			exit(127);
		}
		else if (access(cmd->cmd, R_OK) != 0)
		{
			ft_printf(2, "minishell: %s: Permission denied\n", cmd->cmd);
			exit(126);
		}

	}
	if (!ft_isalpha(*(cmd->cmd)) && is_directory(cmd->cmd))
	{
		ft_printf(2, "minishell: %s: Is a directory\n", cmd->cmd);
		exit(126);
	}
	if (!cmd_name)
	{
		if (execve(cmd->cmd, argv_cmd, env_lst) == -1)
		{
			ft_printf(2, "minishell: %s: command not found\n", cmd->cmd);
			exit(127);
		}
	}
	if (execve(cmd_name, argv_cmd, env_lst) == -1)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->cmd);
		exit(127);
	}
}

static void	process_others_cmd(t_cmd *cmd, t_env **env_lst, t_data *data,
int *ack)
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
		cmd_name = find_cmd(cmd, *env_lst, &data->error);
	argv_cmd = join_params(cmd);
	*ack = 42;
	pid = fork();
	if (pid == -1)
		data_close_and_exit(data, 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		data_close_all_fd(data);
		execute_child_process(cmd_name, argv_cmd, test_env, cmd);
		if (data->error == 127)
			data_close_and_exit(data, 127);
	}
	waitpid(pid, &status, 0);
	data->error = WEXITSTATUS(status);
	if (data->error)
		data_close_and_exit(data, data->error);
}

static void	exec_cmd(t_cmd *cmd, t_data *data, t_env **env_lst, int *flag_exit)
{
	extern int	ack;

	save_return_val(data, env_lst);
	if (data->flag_erropen == true && !data->flag_fork)
		return;
	if (cmd->params)
		cmd_filter_params(&cmd);
	if (!ft_strcmp(cmd->cmd, "echo"))
		execute_echo(cmd, *env_lst);
	data->error = 0;
	if (!ft_strcmp(cmd->cmd, "pwd"))
		execute_pwd(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		execute_unset(cmd, data, env_lst);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		execute_cd(*env_lst, cmd, data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		execute_export(env_lst, cmd, data);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		execute_exit(cmd, data, flag_exit);
	else if (!ft_strcmp(cmd->cmd, "env"))
		execute_env(*env_lst, cmd, data);
	else if (ft_strcmp(cmd->cmd, "echo"))
		process_others_cmd(cmd, env_lst, data, &ack);
	ack = 0;
}

void	exec(t_ast *ast, t_env **env_lst, int *flag_exit, t_data *data)
{
	t_cmd		*cmd;

	ast->content = ft_strtrim(ast->content, " ");
	cmd = NULL;
	cmd = exec_create_cmd(ast->content);
	trim_cmd_and_options(cmd);
	exec_cmd(cmd, data, env_lst, flag_exit);
	cleanup_cmd(cmd);
}
