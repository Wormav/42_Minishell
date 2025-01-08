/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/08 16:03:29 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <token.h>

t_ast	*ast_node_init(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->token = token;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}
	return (node);
}

void	ast_push(t_ast **ast, t_ast *node)
{
	t_ast	*tmp;

	tmp = *ast;
	if (!*ast)
	{
		*ast = node;
		return ;
	}
	if (node->token->type & 1)
	{
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = node;
	}
	else
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = node;
	}
}

t_ast	*ast_create(t_token *lst)
{
	t_ast	*ast = NULL;
	
	t_token *tmp = lst;
	while (tmp)
	{
		ast_push(&ast, ast_node_init(tmp));
		tmp = tmp->next;
	}
	return (ast);
}

void	ast_free(t_ast *ast)
{
	if (!ast)
		return;
	ast_free(ast->left);
	ast_free(ast->right);
	free(ast);
}
