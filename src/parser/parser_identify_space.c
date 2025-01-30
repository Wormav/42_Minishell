/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identify_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:59:04 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 16:07:43 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_next_file_with_spaces(t_token *lst)
{
	if (lst->next && lst->next->next)
	{
		if (lst->type == TOKEN_REDIR_OUT
			&& lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->next->type = TOKEN_FILE;
		if (lst->type == TOKEN_APPEND
			&& lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->next->type = TOKEN_FILE;
		if (lst->type == TOKEN_REDIR_IN
			&& lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->next->type = TOKEN_FILE;
		if (lst->type == TOKEN_HEREDOC
			&& lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->next->type = TOKEN_LIMITER;
	}
}

void	set_next_cmd_with_spaces(t_token *lst)
{
	if (lst->next && lst->next->next)
	{
		if (lst->type == TOKEN_PIPE && lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_FILE && lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_LIMITER && lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_HEREDOC && lst->next->type == TOKEN_SPACE
			&& lst->next->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
	}
}
