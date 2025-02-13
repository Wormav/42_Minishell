/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 17:46:12 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_env_param(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			if (ft_strncmp(str + i, "env", 3) != 0)
				return (0);
			i += 3;
			if (str[i++] != quote)
				return (0);
		}
		else if (ft_strncmp(str + i, "env", 3) == 0)
			i += 3;
		else if (str[i] != ' ')
			return (0);
		else
			i++;
	}
	return (1);
}

void	print_without_prefix(char *str)
{
	if (!str || ft_strlen(str) <= 11)
		return ;
	printf("%s\n", str + 11);
}

void	execute_env(t_env *env, t_cmd *cmd, t_data *data)
{
	if (cmd->options)
	{
		data->error = 2;
		ft_printf(2, "%s\n", handle_bad_option(cmd->options[0], "env"));
		return ;
	}
	if ((!*(cmd->params) && !cmd->options) || check_env_param(cmd->params))
	{
		while (env)
		{
			if (ft_strncmp(env->content, "?=", 2))
				printf("%s\n", (char *)env->content);
			env = env->next;
		}
		return ;
	}
	data->error = 1;
	if (*(cmd->params))
		ft_printf(2, "minishell: env: too many argument\n");
}
