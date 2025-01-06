/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/06 13:31:14 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>

t_ast_node *ast_add_node(t_token *type)
{
	t_ast_node *new;

	new = malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->type = *type;
	return (new);
}

void		ast_free(t_ast_node *root)
{
	if (!root)
		return ;
	ast_free(root->left);
	ast_free(root->right);
	free(root);
}

t_ast_node	*ast_join(t_ast_node *left, t_ast_node *right, t_token *type)
{
	t_ast_node *new = ast_add_node(type);

	new->left = left;
	new->right = right;
	if (left != NULL)
		left->parent = new;
	if (right != NULL)
		right->parent = new;
	return (new);
}
