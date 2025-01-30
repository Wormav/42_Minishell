/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:26:10 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:32 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	cmd_size(t_cmd *cmd)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	if (cmd->params)
		size++;
	if (!cmd->options)
		return (size + 1);
	while (cmd->options[i])
	{
		size++;
		i++;
	}
	return (size + 1);
}

void	fill_params_array(char **str, t_cmd *cmd, int *i)
{
	int	j;

	j = -1;
	if (cmd->options)
	{
		while (cmd->options[++j])
		{
			str[*i] = lp_alloc(ft_strlen(cmd->options[j]) + 1);
			ft_strlcpy(str[*i], cmd->options[j], ft_strlen(cmd->options[j])
				+ 1);
			(*i)++;
		}
	}
	if (cmd->params && *(cmd->params))
	{
		str[*i] = lp_alloc(ft_strlen(cmd->params) + 1);
		ft_strlcpy(str[*i], cmd->params, ft_strlen(cmd->params) + 1);
		(*i)++;
	}
	str[*i] = NULL;
}

char	**join_params(t_cmd *cmd)
{
	char	**str;
	int		i;

	str = lp_alloc(sizeof(char *) * (cmd_size(cmd) + 1));
	i = 0;
	str[i] = lp_alloc(ft_strlen(cmd->cmd) + 1);
	ft_strlcpy(str[i], cmd->cmd, ft_strlen(cmd->cmd) + 1);
	i++;
	fill_params_array(str, cmd, &i);
	return (str);
}
