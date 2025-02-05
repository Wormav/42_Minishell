/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:22:39 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/05 14:43:06 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*parser_del_spaces(t_token *list)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;
	t_token	*head;

	tmp = list;
	prev = NULL;
	head = list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == TOKEN_SPACE)
		{
			if (tmp == head)
				head = next;
			else
				prev->next = next;
			lp_free(tmp);
		}
		else
			prev = tmp;
		tmp = next;
	}
	return (head);
}

static t_token	*pipe_cmd(t_token *list)
{
	t_token	*head;

	if (!list)
		return (NULL);
	head = list;
	while (list)
	{
		if (list->type == TOKEN_PIPE && list->next->type == TOKEN_WORD)
			list->next->type = TOKEN_CMD;
		list = list->next;
	}
	return (head);
}

static int	check_heredoc(t_token *list)
{
	while (list)
	{
		if (list->type == TOKEN_HEREDOC)
			return (1);
		list = list->next;
	}
	return (0);
}

t_token	*parser_join_tokens(t_token *list)
{
	int	flag_heredoc;

	flag_heredoc = check_heredoc(list);
	if (!list)
		return (NULL);
	list = parser_join_word_and_cmd(list, flag_heredoc);
	if (flag_heredoc)
		list = parser_del_spaces(list);
	list = parser_join_redir_and_file(list);
	list = parser_join_heredoc_and_file(list);
	list = parser_join_file_and_redir_in(list);
	if (flag_heredoc)
	{
		list = pipe_cmd(list);
		list = parser_join_word_and_cmd(list, 2);
	}
	return (list);
}
