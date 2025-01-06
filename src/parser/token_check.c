/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:11:30 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 16:16:52 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser_check(t_token *lst)
{
	if (check_quote(lst))
		return (ERR_QUOTE);
	if(check_dquote(lst))
		return (ERR_DQUOTE);
	if (check_parenthesis(lst))
		return (ERR_PARENTHESIS);
	return (0);
}
