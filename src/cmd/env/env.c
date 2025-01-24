/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/24 16:34:10 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*handle_bad_option(char *option)
{
	char	*error_message;
	char	*invalid_option;

	invalid_option = ft_substr(option, 0, 2);
	if (!invalid_option)
		return (NULL);
	error_message = lp_alloc(ft_strlen("bash: env: ")
			+ ft_strlen(invalid_option)
			+ ft_strlen(": invalid option\n") + 1);
	if (!error_message)
	{
		lp_free(invalid_option);
		return (NULL);
	}
	ft_strlcpy(error_message, "bash: env: ", ft_strlen("bash: env: ") + 1);
	ft_strlcat(error_message, invalid_option, ft_strlen(error_message)
		+ ft_strlen(invalid_option) + 1);
	ft_strlcat(error_message, ": invalid option\n", ft_strlen(error_message)
		+ ft_strlen(": invalid option\n") + 1);
	lp_free(invalid_option);
	return (error_message);
}

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
		return (handle_bad_option(cmd->options[0]));
	if (*(cmd->params))
		return (ft_strdup("bash: env: too many argument\n"));
	return (NULL);
}
