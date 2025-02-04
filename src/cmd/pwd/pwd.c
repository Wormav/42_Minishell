/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:20:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/04 17:38:31 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_cmd *cmd, long *error)
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
				*error = 2;
				printf("%s\n", handle_bad_option(cmd->options[i], "pwd"));
				return ;
			}
			i++;
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	result = ft_strjoin(pwd, "\n");
	free(pwd);
	printf("%s", result);
}
