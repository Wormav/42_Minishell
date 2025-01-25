/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:20:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/25 19:40:45 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*execute_pwd(t_cmd *cmd, int *error)
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
			{
				*error = 1;
				return (handle_bad_option(cmd->options[i], "pwd"));
			}
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
