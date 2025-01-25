/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/25 16:13:05 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*execute_env(t_env *env, t_cmd *cmd, int *error)
{
	if (!*(cmd->params) && !cmd->options)
	{
		while (env)
		{
			if (ft_strncmp("declare -x ", env->content, 11))
				printf("%s\n", (char *)env->content);
			env = env->next;
		}
		return (NULL);
	}
	*error = 1;
	if (cmd->options)
		return (handle_bad_option(cmd->options[0], "env"));
	if (*(cmd->params))
		return (ft_strdup("bash: env: too many argument\n"));
	return (NULL);
}
