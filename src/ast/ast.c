/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 08:44:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
