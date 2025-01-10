/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_not_supported.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/10 17:28:01 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

void	check_unsupported_char(t_token *lst, int *flag)
{
	while (lst)
	{
		if (lst->type == TOKEN_D_AND || lst->type == TOKEN_L_PARENTHESIS || lst->type == TOKEN_R_PARENTHESIS || lst->type == TOKEN_DPIPE)
		{
			*flag = 1;
			return;
		}
		lst = lst->next;
	}
}
