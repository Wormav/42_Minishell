/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:23:22 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/11 13:05:40 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ast_split_left(t_token *list, t_token *lowest, t_token **left)
{
	t_token	*current;
	t_token	*left_current;

	*left = NULL;
	current = list;
	while (current && current != lowest)
	{
		if (!*left)
		{
			*left = token_init(current->content, current->type,
					current->priority);
			(*left)->index = current->index;
			left_current = *left;
		}
		else
		{
			left_current->next = token_init(current->content, current->type,
					current->priority);
			left_current->index = current->index;
			left_current = left_current->next;
		}
		current = current->next;
	}
}

static void	ast_split_right(t_token *current, t_token **right)
{
	t_token	*right_current;

	*right = NULL;
	while (current)
	{
		if (!*right)
		{
			*right = token_init(current->content, current->type,
					current->priority);
			(*right)->index = current->index;
			right_current = *right;
		}
		else
		{
			right_current->next = token_init(current->content, current->type,
					current->priority);
			right_current->index = current->index;
			right_current = right_current->next;
		}
		current = current->next;
	}
}

void	ast_split_token_list(t_token *list, t_token *lowest,
		t_token **left, t_token **right)
{
	t_token	*current;

	ast_split_left(list, lowest, left);
	current = list;
	while (current && current != lowest)
		current = current->next;
	if (current)
		current = current->next;
	ast_split_right(current, right);
}
