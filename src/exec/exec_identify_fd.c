/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_identify_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:20:27 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 16:21:12 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_free_fds(t_fds *fds)
{
	t_fds	*tmp;

	while (fds)
	{
		tmp = fds->next;
		if (fds->fd_name)
			lp_free(fds->fd_name);
		lp_free(fds);
		fds = tmp;
	}
}

char	*exec_identify_fd(t_ast *ast)
{
	char	*left;
	char	*right;

	if (!ast)
		return (NULL);
	if (ast->token == TOKEN_REDIR_OUT
		|| ast->token == TOKEN_APPEND)
		return (ast->content);
	left = exec_identify_fd(ast->left);
	right = exec_identify_fd(ast->right);
	if (left)
		return (left);
	if (right)
		return (right);
	return (NULL);
}

char	*exec_identify_se(t_ast *ast)
{
	char	*left;
	char	*right;

	if (!ast)
		return (NULL);
	if (ast->token == TOKEN_REDIR_IN)
		return (ast->content);
	left = exec_identify_se(ast->left);
	right = exec_identify_se(ast->right);
	if (left)
		return (left);
	if (right)
		return (right);
	return (NULL);
}

void	exec_store_other_fds(t_ast *ast, t_fds **list, char *main_fd)
{
	t_fds	*new;

	if (!ast || !list || !main_fd)
		return ;
	if ((ast->token == TOKEN_REDIR_OUT || ast->token == TOKEN_FILE
			|| ast->token == TOKEN_APPEND)
		&& ft_strcmp(ast->content, main_fd) != 0)
	{
		new = lp_alloc(sizeof(t_fds));
		if (!new)
			return ;
		new->fd_name = ft_strdup(ast->content);
		if (!new->fd_name)
		{
			lp_free(new);
			return ;
		}
		new->next = *list;
		*list = new;
	}
	exec_store_other_fds(ast->left, list, main_fd);
	exec_store_other_fds(ast->right, list, main_fd);
}
