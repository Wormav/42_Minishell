/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:44:42 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 09:54:43 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

void	token_push(t_token **lst, t_token *token)
{
	t_token	*tmp;

	if (token_listsize(*lst) == 0)
	{
		*lst = token;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}
