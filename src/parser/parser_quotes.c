/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:19:29 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 17:15:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	join_tokens_quotes(t_token *current)
{
	char	*temp_str;
	t_token	*to_lp_free;

	temp_str = ft_strjoin(current->content, current->next->content);
	if (!temp_str)
		return (0);
	lp_free(current->content);
	current->content = temp_str;
	to_lp_free = current->next;
	current->next = to_lp_free->next;
	lp_free(to_lp_free->content);
	lp_free(to_lp_free);
	return (1);
}

static t_token	*process_quotes(t_token *start)
{
	t_token	*current;

	current = start->next;
	while (current && current->type != TOKEN_QUOTE)
	{
		if (!join_tokens_quotes(start))
			return (start);
		current = start->next;
	}
	if (current && current->type == TOKEN_QUOTE)
	{
		if (!join_tokens_quotes(start))
			return (start);
		return (start->next);
	}
	return (start);
}

static t_token	*parser_quotes(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == TOKEN_QUOTE)
			current = process_quotes(current);
		else
			current = current->next;
	}
	return (list);
}

t_token	*parser_quotes_dquotes(t_token *list)
{
	list = parser_quotes(list);
	list = parser_dquotes(list);
	return (list);
}
