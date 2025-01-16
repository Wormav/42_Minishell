/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:33:28 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/16 11:56:31 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_space(char *str)
{
	char *start;

	start = str;
	while (*str && *str == ' ')
		str++;
	return (str - start);
}

int	find_next_size(char *str)
{
	char *start;
	int i;

	i = 0;
	start = str;
	while (*str && *str != ' ')
		str++;
	return ((str - start) - i);
}

int	check_opts(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str == '-');
}
void	fill_opts(char **to_fill, char *str)
{
	int i;

	i = 0;
	to_fill = malloc(sizeof(char *) * 3);
	while (*str && check_opts(str))
	{
		str += skip_space(str);
		to_fill[i] = ft_substr(str, 0, find_next_size(str));
		i++;
		str += find_next_size(str);
		str += skip_space(str);
	}
}

t_cmd *exec_create_cmd(t_ast *node)
{
    t_cmd	*cmd;
	int 	next_size;
	int		flag;

	next_size = 0;
	flag = 0;
	cmd = malloc(sizeof(t_cmd));
	while (*(node->content))
	{
		next_size = find_next_size(node->content);
		if (!flag)
		{
			cmd->cmd = ft_substr(node->content, 0, next_size);
			flag = 1;
			node->content += next_size;
		}
		if (flag == 1 && check_opts(node->content))
		{
			fill_opts(cmd->options, node->content);
			flag = 2;
		}
		if (flag == 2)
		{
			cmd->params = ft_strdup(node->content);
			return (cmd);
		}
		else
			break;
		}
	return (NULL);
}
