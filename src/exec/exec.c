/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/14 09:03:55 by jlorette         ###   ########.fr       */
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

static void	check_command_access(t_cmd *cmd)
{
	cmd->cmd = ft_strtrim(cmd->cmd, "\t ");
	if ((!ft_strncmp(cmd->cmd, "./", 2) || *(cmd->cmd) == '/'))
	{
		if (is_directory(cmd->cmd))
		{
			ft_printf(2, "minishell: %s: Is a directory\n", cmd->cmd);
			exit_and_clear_history(126);
		}
		else if (access(cmd->cmd, F_OK) != 0)
		{
			ft_printf(2, "minishell: %s: No such file or directory\n",
				cmd->cmd);
				exit_and_clear_history(127);
		}
		else if (access(cmd->cmd, R_OK) != 0)
		{
			ft_printf(2, "minishell: %s: Permission denied\n", cmd->cmd);
			exit_and_clear_history(126);
		}
	}
	if (!ft_isalpha(*(cmd->cmd)) && is_directory(cmd->cmd))
	{
		ft_printf(2, "minishell: %s: Is a directory\n", cmd->cmd);
		exit_and_clear_history(126);
	}
}

void	execute_child_process(char *cmd_name, char **argv_cmd,
char **env_lst, t_cmd *cmd)
{
	check_command_access(cmd);
	if (!cmd_name)
	{
		if (execve(cmd->cmd, argv_cmd, env_lst) == -1)
		{
			ft_printf(2, "minishell: %s: command not found\n", cmd->cmd);
			rl_clear_history();
			exit(127);
		}
	}
	if (execve(cmd_name, argv_cmd, env_lst) == -1)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->cmd);
		rl_clear_history();
		exit(127);
	}
}

static void	exec_cmd(t_cmd *cmd, t_data *data, t_env **env_lst, int *flag_exit)
{
	save_return_val(data, env_lst);
	if (data->flag_erropen == true && !data->flag_fork)
		return ;
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
		process_others_cmd(cmd, env_lst, data);
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
