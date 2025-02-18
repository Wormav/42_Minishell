/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_others_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:24:16 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/18 12:28:32 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_child_execution(t_cmd *cmd, char **env_arr,
	char *cmd_name, t_data *data)
{
	char	**argv_cmd;

	argv_cmd = join_params(cmd);
	setup_child_signals();
	if (!cmd_name)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->cmd);
		data_close_and_exit(data, 127);
	}
	data_close_all_fd(data);
	execute_child_process(cmd_name, argv_cmd, env_arr, cmd);
	if (data->error == 127)
		data_close_and_exit(data, 127);
}

static char	*prepare_command(t_cmd *cmd, t_env *env_lst, long *error)
{
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
			return (cmd->cmd);
		*error = 127;
		return (NULL);
	}
	else if (ft_strcmp(env_get_value(env_lst, "$PATH"), ":./"))
	{
		if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
			return (NULL);
		else
			return (find_cmd(cmd, env_lst, error));
	}
	else
		return (ft_strjoin("./", cmd->cmd));
}

static void	wait_and_check_status(pid_t pid, t_data *data)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	data->error = WEXITSTATUS(status);
	if (data->error == 1 && data->flag_fork)
		data_close_and_exit(data, data->error);
}

void	process_others_cmd(t_cmd *cmd, t_env **env_lst, t_data *data)
{
	char				**env_arr;
	char				*cmd_name;
	pid_t				pid;
	struct sigaction	sa;

	env_arr = env_tab(*env_lst);
	cmd_name = prepare_command(cmd, *env_lst, &data->error);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_fork;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	pid = fork();
	if (pid == -1)
		data_close_and_exit(data, 1);
	if (pid == 0)
	{
		handle_child_execution(cmd, env_arr, cmd_name, data);
		rl_clear_history();
	}
	wait_and_check_status(pid, data);
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
