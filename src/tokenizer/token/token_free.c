/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:55:31 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:55:35 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_token(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		lp_free((char *)lst->content);
		lp_free(lst);
		lst = tmp;
	}
	lp_free(lst);
}
