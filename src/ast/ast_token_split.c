/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:23:22 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/10 11:31:29 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
#include <token.h>
#include <debug.h>

static void	ast_split_left(t_token *list, t_token *lowest, t_token **left)
{
    t_token	*current;
    t_token	*left_current;

    current = list;
    *left = NULL;
    while (current && current != lowest)
    {
        if (current->priority == -1)
        {
            current = current->next;
            continue;
        }
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
}

static void	ast_split_right(t_token *current, t_token **right)
{
    t_token	*right_current;

    *right = NULL;
    while (current)
    {
        if (current->priority == -1)
        {
            current = current->next;
            continue;
        }
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

void	ast_split_token_list(t_token *list, t_token *lowest, t_token **left, t_token **right)
{
    t_token	*current;

    if (!list || !lowest)
        return;
    ast_split_left(list, lowest, left);
    current = list;
    while (current && current != lowest)
        current = current->next;
    if (current)
        current = current->next;
    ast_split_right(current, right);
}
