/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:52:02 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 12:13:04 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	join_tokens(t_token *current)
{
	char	*temp_str;
	t_token	*to_lp_free;

	temp_str = NULL;
	temp_str = ft_strjoin(current->content, "");
	if (!temp_str)
		return (0);
	lp_free(current->content);
	current->content = temp_str;
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

t_token	*parser_join_word_and_cmd(t_token *list)
{
	t_token	*head;
	t_token	*current;

	if (!list)
		return (NULL);
	head = list;
	current = list;
	while (current && current->next)
	{
		if ( current->type == TOKEN_CMD && cmd_content_only_space(current))
			current->type = TOKEN_SPACE;
		if (current->type == TOKEN_CMD && (current->next->type == TOKEN_WORD
				|| current->next->type == TOKEN_ARGS
				|| current->next->type == TOKEN_WAVE
				|| current->next->type == TOKEN_SPACE
				|| current->next->type == TOKEN_VAR))
		{
			if (!join_tokens(current))
				return (head);
		}
		else
			current = current->next;
	}
	return (head);
}

t_token	*parser_join_redir_and_file(t_token *list)
{
	t_token	*head;
	t_token	*current;

	if (!list)
		return (NULL);
	head = list;
	current = list;
	while (current && current->next)
	{
		if ((current->type == TOKEN_REDIR_OUT
				|| current->type == TOKEN_APPEND)
			&& (current->next->type == TOKEN_FILE
				|| current->next->type == TOKEN_SPACE))
		{
			if (!join_tokens(current))
				return (head);
		}
		else
			current = current->next;
	}
	return (head);
}

t_token	*parser_join_heredoc_and_file(t_token *list)
{
	t_token	*head;
	t_token	*current;

	if (!list)
		return (NULL);
	head = list;
	current = list;
	while (current && current->next)
	{
		if (current->type == TOKEN_HEREDOC
			&& (current->next->type == TOKEN_LIMITER
				|| current->next->type == TOKEN_SPACE))
		{
			if (!join_tokens(current))
				return (head);
		}
		else
			current = current->next;
	}
	return (head);
}

t_token	*parser_join_file_and_redir_in(t_token *list)
{
	t_token	*head;
	t_token	*current;

	if (!list)
		return (NULL);
	head = list;
	current = list;
	while (current && current->next)
	{
		if ((current->type == TOKEN_REDIR_IN)
			&& (current->next->type == TOKEN_FILE
				|| current->next->type == TOKEN_SPACE))
		{
			if (!join_tokens(current))
				return (head);
		}
		else
			current = current->next;
	}
	return (head);
}
