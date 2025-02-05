/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:52:47 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 14:38:05 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*read_heredoc(char *delimiter)
{
	char	*line;
	char	*content;

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

t_heredoc	*handle_heredoc(char *delimiter)
{
	t_heredoc	*new;
	int			flag;
	char		*delimiter_trim;

	flag = 1;
	if (!ft_strncmp(delimiter, "\"", 1) || !ft_strncmp(delimiter, "'", 1))
		flag = 0;
	delimiter_trim = ft_strtrim(delimiter, "\"'");
	new = lp_alloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = delimiter_trim;
	new->content = read_heredoc(delimiter_trim);
	new->flag_env = flag;
	return (new);
}

void	free_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	if (heredoc->content)
		lp_free(heredoc->content);
	if (heredoc->delimiter)
		lp_free(heredoc->delimiter);
	lp_free(heredoc);
}
