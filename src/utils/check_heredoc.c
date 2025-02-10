/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:45:57 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/10 13:46:14 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_heredoc(t_token *list)
{
	while (list)
	{
		if (list->type == TOKEN_HEREDOC)
			return (1);
		list = list->next;
	}
	return (0);
}
