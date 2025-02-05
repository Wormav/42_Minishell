/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:39:02 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/05 11:57:30 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_next_cmd(t_token *lst)
{
	if (lst->next && lst->next->type == TOKEN_SPACE)
		set_next_cmd_with_spaces(lst);
	if (lst->type == TOKEN_PIPE && lst->next->type == TOKEN_WORD)
		lst->next->type = TOKEN_CMD;
	if (lst->type == TOKEN_FILE && lst->next->type == TOKEN_WORD)
		lst->next->type = TOKEN_CMD;
	if (lst->type == TOKEN_LIMITER && lst->next->type == TOKEN_WORD)
		lst->next->type = TOKEN_CMD;
}

static t_token	*parser_identify_cmd(t_token *lst)
{
	t_token	*tmp;
	int		first_flag;

	tmp = lst;
	first_flag = 0;
	while (lst)
	{
		if (lst->type == TOKEN_WORD && !first_flag)
		{
			first_flag = 1;
			lst->type = TOKEN_CMD;
		}
		if (lst->type != TOKEN_SPACE && lst->next)
		{
			if (!cmd_content_only_space(lst))
				set_next_cmd(lst);
		}
		lst = lst->next;
	}
	return (tmp);
}

static t_token	*parser_identify_files(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (lst->next)
	{
		if (lst->next && lst->next->type == TOKEN_SPACE)
			set_next_file_with_spaces(lst);
		else if (lst->type == TOKEN_REDIR_IN && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_REDIR_OUT && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_APPEND && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_HEREDOC && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_LIMITER;
		if (lst->next->type == TOKEN_WILDCARD)
			lst->next->type = TOKEN_WORD;
		lst = lst->next;
	}
	return (tmp);
}

t_token	*parser_identify(t_token *list)
{
	list = parser_identify_files(list);
	list = parser_identify_cmd(list);
	return (list);
}
