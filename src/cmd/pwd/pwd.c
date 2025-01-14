/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:20:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/14 20:40:44 by jlorette         ###   ########.fr       */
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
	error_message = malloc(ft_strlen("bash: pwd: ") + ft_strlen(invalid_option)
			+ ft_strlen(": invalid option\n") + 1);
	if (!error_message)
	{
		free(invalid_option);
		return (NULL);
	}
	ft_strlcpy(error_message, "bash: pwd: ", ft_strlen("bash: pwd: ") + 1);
	ft_strlcat(error_message, invalid_option, ft_strlen(error_message)
		+ ft_strlen(invalid_option) + 1);
	ft_strlcat(error_message, ": invalid option\n", ft_strlen(error_message)
		+ ft_strlen(": invalid option\n") + 1);
	free(invalid_option);
	return (error_message);
}

char	*execute_pwd(t_cmd *cmd)
{
	char	*pwd;
	char	*result;
	int		i;

	i = 0;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			if (cmd->options[i][1])
				return (handle_bad_option(cmd->options[i]));
			i++;
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	result = ft_strjoin(pwd, "\n");
	free(pwd);
	return (result);
}
