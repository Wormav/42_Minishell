/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:59:04 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/04 17:33:19 by jlorette         ###   ########.fr       */
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
	while (fd[start] && (fd[start] == '>' || fd[start] == '<'))
		start++;
	trimmed = ft_strdup(fd + start);
	trimmed = ft_strtrim(trimmed, " \"'");
	return (trimmed);
}

int	define_macro(char *fd)
{
	if (!ft_strncmp(fd, ">>", 2))
		return (O_APPEND);
	else
		return (O_TRUNC);
}

void	exec_ast_next(t_ast *ast, t_env **env_lst)
{
	int		pipefd[2];
	int		flag_exit;

	flag_exit = 0;
	if (ast->parent && ast->parent->token == TOKEN_PIPE)
		flag_exit = 1;
	if (!ast)
		return ;
	while (ast && ast->token != TOKEN_CMD && ast->token != TOKEN_PIPE)
		ast = ast->left;
	if (!ast)
		return ;
	if (ast->token == TOKEN_PIPE)
		handle_pipe(ast, env_lst, pipefd);
	else if (ast->token == TOKEN_CMD)
		exec(ast, env_lst, &flag_exit);
}

void	exec_setup_fds(t_ast *ast, t_fds **fds, char **fd, char **fd_trim)
{
	*fd = exec_identify_fd(ast);
	if (*fd)
		*fd_trim = exec_trim_fd(*fd);
	exec_store_other_fds(ast, fds, *fd);
}
