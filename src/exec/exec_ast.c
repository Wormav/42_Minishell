/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:26 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 12:18:53 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_ast_right(t_ast *ast, t_env *env_lst)
{
	int		pipefd[2];
	pid_t	pid;

	pid = 0;
	if (!ast)
		return ;
	if (ast->token == TOKEN_PIPE)
		handle_pipe(ast, env_lst, pipefd, pid);
	else
		exec(ast, env_lst);
}

void	handle_pipe(t_ast *ast, t_env *env_lst, int pipefd[2], pid_t pid)
{
	if (pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_ast_right(ast->left, env_lst);
		exit(0);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exec(ast->right, env_lst);
	wait(NULL);
}

void	exec_ast(t_ast *ast, t_env *env_lst)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!ast || !env_lst)
		return ;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	exec_ast_right(ast, env_lst);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
