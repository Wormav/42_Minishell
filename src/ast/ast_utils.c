/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:17:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/09 14:50:32 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
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

void	ast_free(t_ast *ast)
{
	if (!ast)
		return;
	ast_free(ast->left);
	ast_free(ast->right);
	free(ast);
}

t_token *ast_find_lowest_priority_token(t_token *list)
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

void ast_split_token_list(t_token *list, t_token *lowest, t_token **left, t_token **right)
{
    t_token *current;
    t_token *left_current;
    t_token *right_current;

    *left = NULL;
    *right = NULL;
    current = list;
    while (current && current != lowest)
    {
        if (!*left)
        {
            *left = token_init(current->content, current->type, current->priority);
			left_current = *left;
		}
		else
        {
            left_current->next = token_init(current->content, current->type, current->priority);
            left_current = left_current->next;
        }
        current = current->next;
    }
    if (current)
		current = current->next;
	while (current)
    {
        if (!*right)
        {
            *right = token_init(current->content, current->type, current->priority);
            right_current = *right;
        }
        else
        {
            right_current->next = token_init(current->content, current->type, current->priority);
            right_current = right_current->next;
        }
        current = current->next;
    }
}
