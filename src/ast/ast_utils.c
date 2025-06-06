/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:17:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 11:17:14 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*ast_node_init(t_token *token)
{
	t_ast	*node;

	node = lp_alloc(sizeof(t_ast));
	if (node)
	{
		node->content = ft_strdup(token->content);
		node->priority = token->priority;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->token = token->type;
	}
	return (node);
}

void	ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	ast_free(ast->left);
	ast_free(ast->right);
	lp_free(ast->content);
	lp_free(ast);
}

static t_token	*find_lowest_priority(t_token *current, t_token *lowest)
{
	while (current)
	{
		if (current->priority > 0)
		{
			if (current->priority > 1)
			{
				if (current->priority < lowest->priority
					|| (current->priority == lowest->priority
						&& current->index < lowest->index))
					lowest = current;
			}
			else
			{
				if (current->priority < lowest->priority
					|| (current->priority == lowest->priority
						&& current->index > lowest->index))
					lowest = current;
			}
		}
		current = current->next;
	}
	return (lowest);
}

t_token	*ast_find_lowest_priority_token(t_token *list)
{
	t_token	*lowest;
	t_token	*current;

	if (!list)
		return (NULL);
	current = list;
	while (current && current->priority <= 0)
		current = current->next;
	if (!current)
		return (NULL);
	lowest = current;
	return (find_lowest_priority(current, lowest));
}
