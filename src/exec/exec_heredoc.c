/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:52:47 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/31 12:21:31 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *read_heredoc(char *delimiter)
{
	char *line;
	char *content;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		content = ft_strjoin(content, line);
		content = ft_strjoin(content, "\n");
		free(line);
	}
	return (content);
}

t_heredoc *handle_heredoc(char *delimiter)
{
	t_heredoc *new;

	new = lp_alloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = ft_strdup(delimiter);
	new->content = read_heredoc(delimiter);
	new->next = NULL;
	return (new);
}
