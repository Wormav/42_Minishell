/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:39:02 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 11:43:25 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
* @brief
* Objectif:
* 
*
*/

#include "token.h"
#include <parser.h>

//coder les foncitons de parser list

static t_token	*parser_identify_cmd(t_token *lst)
{
	t_token	*tmp;
	int		first_flag;

	tmp = lst;
	first_flag = 0;
	while (lst->next)
	{
		if (lst->type == TOKEN_WORD && !first_flag)
		{
			first_flag = 1;
			lst->type = TOKEN_CMD;
		}
		if (lst->type == TOKEN_PIPE && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;	
		if (lst->type == TOKEN_FILE && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_L_PARENTHESIS && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_D_AND && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
		if (lst->type == TOKEN_DPIPE && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_CMD;
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
		if (lst->type == TOKEN_REDIR_IN && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_REDIR_OUT && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_APPEND && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
		else if (lst->type == TOKEN_HEREDOC && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_LIMITER;
		else if (lst->type == TOKEN_LIMITER && lst->next->type == TOKEN_WORD)
			lst->next->type = TOKEN_FILE;
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
	//list = parser_identify_string(list);
	return (list);
}
