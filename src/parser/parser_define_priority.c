/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_define_priority.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:22 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/09 21:59:38 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_content_only_space(t_token *node)
{
	int	i;

	i = 0;
	while (node->content[i])
	{
		if (node->content[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	define_priority(t_token *node)
{
	if (node->type == TOKEN_PIPE || node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_APPEND || node->type == TOKEN_REDIR_IN
		|| node->type == TOKEN_HEREDOC)
		return (P_OUT_OR_APP_OR_PIPE_OR_HEREDOC);
	if (node->type == TOKEN_CMD)
		return (P_CMDS);
	if (node->type == TOKEN_CMD && cmd_content_only_space(node))
		return (-1);
	if (node->type == TOKEN_WORD)
		return (P_WORD);
	if (node->type == TOKEN_SPACE)
		return (-1);
	else
		return (P_TOKENS);
}

void	parser_define_priority(t_token **list)
{
	t_token	*tmp;
	int		index;

	if (*list == NULL)
		return;
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
	tmp->priority = define_priority(tmp);
}
