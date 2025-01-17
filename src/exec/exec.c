/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/17 16:33:06 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// !retirer les print

void	exec(t_ast *ast)
{
	t_cmd	*cmd;
	t_fds	*fds;
	char	*fd;

	cmd = NULL;
	fds = NULL;
	fd = exec_identify_fd(ast);
	exec_store_other_fds(ast, &fds, fd);
	print_fds(fds);
	printf("FD =======> [%s]\n", fd);
	cmd = exec_create_cmd(ast->content);
	print_cmd(cmd);
	cleanup_cmd(cmd);
	exec_free_fds(fds);
}
