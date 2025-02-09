/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:11:30 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/09 21:55:29 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	token_check_quote(t_token *lst)
{
	int	quote;

	if (!lst)
		return (0);
	quote = 0;
	while (lst->next)
	{
		quote += (lst->type == TOKEN_QUOTE);
		lst = lst->next;
	}
	quote += (lst->type == TOKEN_QUOTE);
	return (quote % 2);
}

static int	token_check_dquote(t_token *lst)
{
	int	dquote;

	if (!lst)
		return (0);
	dquote = 0;
	while (lst->next)
	{
		dquote += (lst->type == TOKEN_DQUOTE);
		lst = lst->next;
	}
	dquote += (lst->type == TOKEN_DQUOTE);
	return (dquote & 1);
}

int	parser_check(t_token *lst)
{
	if (token_check_quote(lst))
		return (ERR_ODD_QUOTE);
	if (token_check_dquote(lst))
		return (ERR_ODD_DQUOTE);
	return (0);
}
