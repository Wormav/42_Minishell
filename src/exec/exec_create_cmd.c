/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_create_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:33:28 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/11 19:56:29 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cleanup_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd)
		lp_free(cmd->cmd);
	if (cmd->options)
	{
		i = 0;
		while (cmd->options[i])
		{
			lp_free(cmd->options[i]);
			i++;
		}
		lp_free(cmd->options);
	}
	if (cmd->params)
		lp_free(cmd->params);
	lp_free(cmd);
}

static char	*fill_opts(char ***to_fill, char *str)
{
	int	i;
	int	size;

	i = 0;
	while (*str && (check_opts(str) || ((*str == '\'' || *str == '"')
				&& *(str + 1) == '-')))
	{
		str += skip_space(str);
		size = find_next_size(str);
		if (size <= 0)
			break ;
		(*to_fill)[i] = ft_substr(str, 0, size);
		i++;
		str += size;
		str += skip_space(str);
	}
	(*to_fill)[i] = NULL;
	return (str);
}

t_cmd	*exec_create_cmd(char *str)
{
	t_cmd	*cmd;
	char	*trim;
	int		next_size;

	next_size = 0;
	cmd = lp_alloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (str)
	{
		next_size = find_first_size(str);
		cmd->cmd = parser_filter_quote(ft_substr(str, 0, next_size));
		str += next_size;
		if (check_opts(str))
		{
			cmd->options = lp_alloc(sizeof(char *) * (count_args(str) + 1));
			str = fill_opts(&cmd->options, str);
		}
		trim = ft_strtrim(str, " ");
		cmd->params = trim;
		return (cmd);
	}
	return (NULL);
}
