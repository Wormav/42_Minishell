/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_others_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:24:16 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 14:58:01 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


static void	handle_child_execution(t_cmd *cmd, char **test_env,
	char *cmd_name, t_data *data)
{
	char	**argv_cmd;

	argv_cmd = join_params(cmd);
	setup_child_signals();
	data_close_all_fd(data);
	execute_child_process(cmd_name, argv_cmd, test_env, cmd);
	if (data->error == 127)
		data_close_and_exit(data, 127);
}

static char	*prepare_command(t_cmd *cmd, t_env *env_lst, long *error)
{
	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		return (cmd->cmd);
	return (find_cmd(cmd, env_lst, error));
}

static void	wait_and_check_status(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	data->error = WEXITSTATUS(status);
	if (data->error == 1)
		data_close_and_exit(data, data->error);
}

static void handler_fork(int sig)
{
	extern int ack;
	(void)sig;
	if (sig == SIGINT)
    {
		ack = 130;
		write(1, "\n", 1);
	}
    else if (sig == SIGQUIT)
    {
		ack = 131;
		write(1, "Quit\n", 5);
	}
}

void process_others_cmd(t_cmd *cmd, t_env **env_lst, t_data *data)
{
    char **test_env;
    char *cmd_name;
    pid_t pid;
    struct sigaction sa;

    test_env = env_tab(*env_lst);
    cmd_name = prepare_command(cmd, *env_lst, &data->error);
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_fork;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    pid = fork();
    if (pid == -1)
        data_close_and_exit(data, 1);
    if (pid == 0)
        handle_child_execution(cmd, test_env, cmd_name, data);
    wait_and_check_status(pid, data);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
