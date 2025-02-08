/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:43:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/07 16:46:08 by jlorette         ###   ########.fr       */
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

void	handle_pipe_child_right(t_ast *ast, t_env **env_lst,
int pipefd[2], t_data *data)
{
	int	flag_exit;

	flag_exit = 1;
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (ast->right->token == TOKEN_CMD)
		exec(ast->right, env_lst, &flag_exit, data);
	else
		exec_ast_next(ast->right, env_lst, data);
	data_close_and_exit(data, EXIT_SUCCESS);
}

void	handle_pipe(t_ast *ast, t_env **env_lst, int pipefd[2], t_data *data)
{
	pid_t	pids[2];

	if (pipe(pipefd) == -1)
		return ;
	pids[0] = fork();
	if (pids[0] == -1)
		return ;
	if (pids[0] == 0)
		handle_pipe_child_left(ast, env_lst, pipefd, data);
	close(pipefd[1]);
	data->flag_fork = true;
	pids[1] = fork();
	if (pids[1] == -1)
	{
		data->flag_fork = false;
		close(pipefd[0]);
		waitpid(pids[0], NULL, 0);
		return ;
	}
	if (pids[1] == 0)
		handle_pipe_child_right(ast, env_lst, pipefd, data);
	close(pipefd[0]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	data->flag_fork = false;
}
