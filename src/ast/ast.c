/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/09 19:39:08 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
#include <token.h>

void	cleanup_token_list(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	relink(t_token *node)
{
	t_token	*free_node;

	if (!node || !node->next)
		return ;
	free_node = node->next;
	node->next = free_node->next;
	free(node->content);
	free(free_node);
}

t_ast	*ast_create(t_token *lst, t_ast *root)
{
	t_token	*left;
	t_token	*right;
	t_token	*lowest;

	left = NULL;
	right = NULL;
	if (!lst)
		return (NULL);
	lowest = ast_find_lowest_priority_token(lst);
	if (!lowest)
		return (NULL);
	root = ast_node_init(lowest);
	if (token_listsize(lst) == 0)
		return (NULL);
	ast_split_token_list(lst, lowest, &left, &right);
	if (root && token_listsize(lst) > 1)
	{
		root->left = ast_create(left, root->left);
		root->right = ast_create(right, root->right);
		free_token(left);
		free_token(right);
	}
	return (root);
}
