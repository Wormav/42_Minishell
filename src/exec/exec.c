/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:33:28 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/16 14:59:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*fill_opts(char ***to_fill, char *str)
{
	int	i;

	i = 0;
	while (*str && check_opts(str))
	{
		str += skip_space(str);
		(*to_fill)[i] = ft_substr(str, 0, find_next_size(str));
		i++;
		str += find_next_size(str);
		str += skip_space(str);
	}
	(*to_fill)[i] = NULL;
	return (str);
}

t_cmd	*exec_create_cmd(t_ast *node)
{
	t_cmd	*cmd;
	int		next_size;

	next_size = 0;
	cmd = malloc(sizeof(t_cmd));
	while (*(node->content))
	{
		next_size = find_next_size(node->content);
		cmd->cmd = ft_substr(node->content, 0, next_size);
		node->content += next_size;
		if (check_opts(node->content))
		{
			cmd->options = malloc(sizeof(char *)
					* count_args(node->content) + 1);
			node->content = fill_opts(&cmd->options, node->content);
		}
		cmd->params = ft_strdup(node->content);
		return (cmd);
	}
	return (NULL);
}
