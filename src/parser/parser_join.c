/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:22:39 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/10 13:45:40 by jlorette         ###   ########.fr       */
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

static char	*join_cmd_content(t_token *tmp)
{
	t_token	*curr;
	char	*new_content;
	char	*temp;

	new_content = ft_strdup(tmp->content);
	curr = tmp->next;
	while (curr && curr->type != TOKEN_PIPE)
	{
		if (curr->type == TOKEN_CMD)
		{
			temp = new_content;
			new_content = ft_strjoin(temp, curr->content);
			lp_free(temp);
			curr->type = TOKEN_WORD;
		}
		curr = curr->next;
	}
	return (new_content);
}

static t_token	*join_cmd(t_token *list)
{
	t_token	*head;
	t_token	*tmp;
	char	*new_content;

	tmp = list;
	head = list;
	while (tmp)
	{
		if (tmp->type == TOKEN_CMD)
		{
			new_content = join_cmd_content(tmp);
			lp_free(tmp->content);
			tmp->content = new_content;
		}
		tmp = tmp->next;
	}
	return (head);
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
	list = join_cmd(list);
	return (list);
}
