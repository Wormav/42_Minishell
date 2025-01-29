/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 09:18:51 by jlorette         ###   ########.fr       */
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

char	*execute_env(t_env *env, t_cmd *cmd, int *error)
{
	if (cmd->options)
		return (handle_bad_option(cmd->options[0], "env"));
	if ((!*(cmd->params) && !cmd->options) || check_env_param(cmd->params))
	{
		while (env)
		{
			if (ft_strncmp("declare -x ", env->content, 11))
				printf("%s\n", (char *)env->content);
			else
				print_without_prefix(env->content);
			env = env->next;
		}
		return (NULL);
	}
	*error = 1;
	if (*(cmd->params))
		return (ft_strdup("bash: env: too many argument\n"));
	return (NULL);
}
