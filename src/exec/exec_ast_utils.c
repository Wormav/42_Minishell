/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:59:04 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 16:43:24 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*exec_trim_fd(char *fd)
{
	char	*trimmed;
	int		start;

	if (!fd)
		return (NULL);
	start = 0;
	while (fd[start] && (fd[start] == '>' || fd[start] == '<'
			|| fd[start] == '<'))
		start++;
	trimmed = ft_strdup(fd + start);
	trimmed = ft_strtrim(trimmed, " ");
	return (trimmed);
}

int	define_macro(char *fd)
{
	if (!ft_strncmp(fd, ">>", 2))
		return (O_APPEND);
	else
		return (O_TRUNC);
}

void	exec_ast_right(t_ast *ast, t_env *env_lst)
{
	int		pipefd[2];
	pid_t	pid;

	pid = 0;
	if (!ast)
		return ;
	while (ast && ast->token != TOKEN_CMD && ast->token != TOKEN_PIPE)
		ast = ast->left;
	if (!ast)
		return ;
	if (ast->token == TOKEN_PIPE)
		handle_pipe(ast, env_lst, pipefd, pid);
	else if (ast->token == TOKEN_CMD)
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
	while (ast->right && ast->right->token != TOKEN_CMD
		&& ast->right->token != TOKEN_PIPE)
		ast->right = ast->right->right;
	if (ast->right)
	{
		if (ast->right->token == TOKEN_CMD)
			exec(ast->right, env_lst);
		else
			exec_ast_right(ast->right, env_lst);
	}
	wait(NULL);
}

void	exec_setup_fds(t_ast *ast, t_fds **fds, char **fd, char **fd_trim)
{
	*fd = exec_identify_fd(ast);
	if (*fd)
		*fd_trim = exec_trim_fd(*fd);
	exec_store_other_fds(ast, fds, *fd);
	print_fds(*fds);
	printf("FD =======> [%s]\n", *fd);
}
