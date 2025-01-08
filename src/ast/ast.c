/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/08 17:40:23 by jlorette         ###   ########.fr       */
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

static t_token *find_lowest_priority_token(t_token *list)
{
	t_token *lowest = list;

	while (list)
	{
		if (list->priority > 1)
		{
			if (list->priority < lowest->priority ||
		   	(list->priority == lowest->priority && list->index < lowest->index))
			{
				lowest = list;
			}
			list = list->next;
		}
		else
		{
			if (list->priority < lowest->priority ||
		   	(list->priority == lowest->priority && list->index > lowest->index))
			{
				lowest = list;
			}
			list = list->next;
		}

	}
	return (lowest);
}

static t_token *remove_lowest_priority_token(t_token *list, t_token *lowest)
{

	t_token *current;
	t_token *previous;

	previous= NULL;
	current = list;
	while (current)
	{
		if (current == lowest)
		{
			if (previous)
				previous->next = current->next;
			else
				list = current->next;
			free(current);
			return list;
		}
		previous = current;
		current = current->next;
	}
	return list;
}

void	ast_push(t_ast **ast, t_ast *node, int side)
{
	t_ast	*tmp;

	tmp = *ast;
	if (!*ast)
	{
		*ast = node;
		return ;
	}
	if (side == 1)
		tmp = node;
	if (side == 2)
		tmp->left = node;
	else if (side == 3)
	  tmp->right = node;
}

t_ast	*ast_create(t_token *lst)
{
	t_ast	*ast = NULL;
	t_token *lowers;
	t_token *lowers_left;
	t_token *lowers_right;

	// t_token *tmp = lst;
	lowers = find_lowest_priority_token(lst);
	lst = remove_lowest_priority_token(lst, lowers);
	lowers_left = find_lowest_priority_token(lst);
	lst = remove_lowest_priority_token(lst, lowers_left);
	lowers_right = find_lowest_priority_token(lst);

	ast_push(&ast, ast_node_init(lowers), 1);
	ast_push(&ast, ast_node_init(lowers_left), 2);
	ast_push(&ast, ast_node_init(lowers_right), 3);
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
