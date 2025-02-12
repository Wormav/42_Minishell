/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:26:10 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/12 10:06:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**handle_quotes(char **str_array, int i)
{
	int	j;

	if (str_array[i + 1] && ft_strlen(str_array[i]) == 1
		&& ft_strlen(str_array[i + 1]) == 1
		&& ((str_array[i][0] == '\'' && str_array[i + 1][0] == '\'')
		|| (str_array[i][0] == '\"' && str_array[i + 1][0] == '\"')))
	{
		str_array[i] = ft_strdup(" ");
		j = i + 1;
		while (str_array[j + 1])
		{
			str_array[j] = str_array[j + 1];
			j++;
		}
		str_array[j] = NULL;
		return (str_array);
	}
	return (NULL);
}

char	**process_quotes_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
	{
		if (handle_quotes(array, i))
			continue ;
		array[i] = parser_filter_quote(array[i]);
		i++;
	}
	return (array);
}

int	cmd_size(t_cmd *cmd)
{
	int	size;
	int	i;

	i = 0;
	size = 1;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			size++;
			i++;
		}
	}
	size += count_params_size(cmd->params);
	return (size + 1);
}

void	fill_params_array(char **str, t_cmd *cmd, int *i)
{
	int		j;
	char	**param_array;

	j = 0;
	if (cmd->options)
	{
		while (cmd->options[j])
		{
			str[*i] = ft_strdup(cmd->options[j]);
			(*i)++;
			j++;
		}
	}
	if (cmd->params && *(cmd->params))
	{
		param_array = ft_split(cmd->params, ' ');
		j = 0;
		while (param_array[j])
		{
			str[*i] = ft_strdup(param_array[j]);
			(*i)++;
			j++;
		}
	}
	str[*i] = NULL;
}

char	**join_params(t_cmd *cmd)
{
	char	**str_array;
	int		i;

	str_array = lp_alloc(sizeof(char *) * (cmd_size(cmd) + 1));
	i = 0;
	str_array[i] = lp_alloc(ft_strlen(cmd->cmd) + 1);
	ft_strlcpy(str_array[i], cmd->cmd, ft_strlen(cmd->cmd) + 1);
	i++;
	fill_params_array(str_array, cmd, &i);
	str_array = process_quotes_array(str_array);
	return (str_array);
}
