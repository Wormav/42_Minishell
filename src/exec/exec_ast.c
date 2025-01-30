/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:26 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 11:53:20 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void exec_ast_right(t_ast *ast, t_env *env_lst)
{
	if (!ast)
		return;
	if (ast->token == TOKEN_PIPE)
	{
		int pipefd[2];
		if (pipe(pipefd) == -1)
			return;
		pid_t pid = fork();
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
	else
		exec(ast, env_lst);
}

void exec_ast(t_ast *ast, t_env *env_lst)
{
	if (!ast || !env_lst)
		return;
	int stdin_backup = dup(STDIN_FILENO);
	int stdout_backup = dup(STDOUT_FILENO);
	exec_ast_right(ast, env_lst);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
