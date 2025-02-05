/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:22:39 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/05 12:29:37 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*parser_del_spaces(t_token *list)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;

	if (!list)
		return (NULL);
	tmp = list;
	prev = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == TOKEN_SPACE)
		{
			if (tmp == list)
				list = next;
			else
				prev->next = next;
			lp_free(tmp);
		}
		else
			prev = tmp;
		tmp = next;
	}
	return (list);
}

static t_token	*pipe_cmd(t_token *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (list->type == TOKEN_PIPE && list->next->type == TOKEN_WORD)
			list->next->type = TOKEN_CMD;
		list = list->next;
	}
	return (list);
}

t_token	*parser_join_tokens(t_token *list)
{
	if (!list)
		return (NULL);
	list = parser_join_word_and_cmd(list);
	list = parser_del_spaces(list);
	list = parser_join_redir_and_file(list);
	list = parser_join_heredoc_and_file(list);
	list = parser_join_file_and_redir_in(list);
	list = pipe_cmd(list);
	return (list);
}
