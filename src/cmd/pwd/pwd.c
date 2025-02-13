/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:20:20 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 17:13:34 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_cmd *cmd, t_data *data)
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
				data->error = 2;
				ft_printf(2, "%s\n", handle_bad_option(cmd->options[i], "pwd"));
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
