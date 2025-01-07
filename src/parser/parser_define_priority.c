/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_define_priority.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:22 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 20:31:44 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <parser.h>

static	int define_priority(t_token *node)
{
	if (node->type == TOKEN_PIPE)
		return (P_PIPE);
	if (node->type == TOKEN_L_PARENTHESIS)
		return (P_PARENTHESIS);
	if (node->type == TOKEN_R_PARENTHESIS)
		return (-1);
	if (node->type == TOKEN_D_AND)
		return (P_DOUBLEAND);
	if (node->type == TOKEN_CMD)
		return (P_CMDS);
	if (node->type == TOKEN_WORD)
		return (P_WORD);
	else
		return (P_TOKENS);
}

void	parser_define_priority(t_token **list)
{
	t_token	*tmp;
	int		index;

	tmp = (*list);
	index = 0;
	while (tmp->next)
	{
		tmp->index = index;
		index++;
		tmp->priority = define_priority(tmp);
		tmp = tmp->next;
	}
	tmp->index = index;
	index++;
	tmp->priority = define_priority(tmp);
}
