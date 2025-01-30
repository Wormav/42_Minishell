/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:22:39 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/30 15:55:55 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*parser_join_tokens(t_token *list)
{
	if (!list)
		return (NULL);
	list = parser_join_word_and_cmd(list);
	list = parser_join_redir_and_file(list);
	list = parser_join_heredoc_and_file(list);
	list = parser_join_file_and_redir_in(list);
	return (list);
}
