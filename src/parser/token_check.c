/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:11:30 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 08:57:04 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <token.h>

static int	token_check_parenthesis(t_token *lst)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (lst->next)
	{
		left += (lst->type == TOKEN_L_PARENTHESIS);
		right += (lst->type == TOKEN_R_PARENTHESIS);
		lst = lst->next;
	}
	left += (lst->type == TOKEN_L_PARENTHESIS);
	right += (lst->type == TOKEN_R_PARENTHESIS);
	return (left == right);
}

static int	token_check_quote(t_token *lst)
{
	int	quote;

	quote = 0;
	while (lst->next)
	{
		quote += (lst->type == TOKEN_QUOTE);
		lst = lst->next;
	}
	quote += (lst->type == TOKEN_QUOTE);
	return (quote & 1);
}

static int	token_check_dquote(t_token *lst)
{
	int	dquote;

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
	if (!token_check_parenthesis(lst))
		return (ERR_ODD_PARENTHESIS);
	return (0);
}
