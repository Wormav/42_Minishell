/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_listsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:48:01 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 09:54:52 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

int	token_listsize(t_token *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}
