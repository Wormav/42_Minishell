/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:45 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/11 13:06:18 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*process_dquotes(t_token *start)
{
	t_token	*current;

	current = start->next;
	while (current && current->type != TOKEN_DQUOTE)
	{
		if (!join_tokens_quotes(start))
			return (start);
		current = start->next;
	}
	if (current && current->type == TOKEN_DQUOTE)
	{
		if (!join_tokens_quotes(start))
			return (start);
		return (start->next);
	}
	return (start);
}

t_token	*parser_dquotes(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == TOKEN_QUOTE)
			current = process_dquotes(current);
		else
			current = current->next;
	}
	return (list);
}
