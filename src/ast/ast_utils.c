/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:17:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/09 19:48:04 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
#include <token.h>
#include <debug.h>

t_ast	*ast_node_init(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->content = ft_strdup(token->content);
		node->priority = token->priority;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}
	return (node);
}

void	ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	ast_free(ast->left);
	ast_free(ast->right);
	free(ast->content);
	free(ast);
}

t_token	*ast_find_lowest_priority_token(t_token *list)
{
	t_token	*lowest;

	if (!list)
		return (NULL);
	lowest = list;
	while (list)
	{
		if (list->priority > 1)
		{
			if (list->priority < lowest->priority
				|| (list->priority == lowest->priority
					&& list->index < lowest->index))
				lowest = list;
			list = list->next;
		}
		else
		{
			if (list->priority < lowest->priority
				|| (list->priority == lowest->priority
					&& list->index > lowest->index))
				lowest = list;
			list = list->next;
		}
	}
	return (lowest);
}
