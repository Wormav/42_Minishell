/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:43:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/18 10:35:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_pipe_child_left(t_ast *ast, t_env **env_lst, int pipefd[2],
t_data *data)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_ast_next(ast->left, env_lst, data);
	data_close_and_exit(data, EXIT_SUCCESS);
}

void	handle_pipe_child_right(t_ast *ast, t_env **env_lst, int pipefd[2],
t_data *data)
{
	int	flag_exit;

	flag_exit = 1;
	if (pipefd)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			ft_printf(2, "minishell: dup2 failed\n");
			data_close_and_exit(data, EXIT_FAILURE);
		}
		close(pipefd[0]);
	}
	if (ast && ast->right)
	{
		if (ast->right->token == TOKEN_CMD)
			exec(ast->right, env_lst, &flag_exit, data);
		else
			exec_ast_next(ast->right, env_lst, data);
	}
	data_close_and_exit(data, EXIT_SUCCESS);
}

static int	init_pipe_left(t_ast *ast, t_env **env_lst, int pipefd[2],
t_data *data)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_pipe_child_left(ast, env_lst, pipefd, data);
	return (pid);
}

void	handle_pipe(t_ast *ast, t_env **env_lst, int pipefd[2], t_data *data)
{
	pid_t	pids[2];
	int		status[2];

	pids[0] = init_pipe_left(ast, env_lst, pipefd, data);
	if (pids[0] == -1)
		return ;
	close(pipefd[1]);
	data->flag_fork = true;
	pids[1] = fork();
	if (pids[1] == -1)
	{
		data->flag_fork = false;
		close(pipefd[0]);
		waitpid(-1, NULL, 0);
		return ;
	}
	if (pids[1] == 0)
		handle_pipe_child_right(ast, env_lst, pipefd, data);
	close(pipefd[0]);
	waitpid(pids[1], &status[1], 0);
	waitpid(pids[0], &status[0], 0);
	data->error = WEXITSTATUS(status[1]);
	data->flag_fork = false;
}
