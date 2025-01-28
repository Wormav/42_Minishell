/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/28 15:32:52 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int check_option_n(char *str)
{
	int i;

	if (!str || str[0] != '-' || !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int count_option_n(char **options)
{
	int count;
	int i;

	if (!options)
		return (0);
	count = 0;
	i = 0;
	while (options[i] && check_option_n(options[i]))
	{
		count++;
		i++;
	}
	return (count);
}

void ft_echo(t_cmd *cmd, int *error)
{
	(void)error;
	int i;
	int save;

	i = count_option_n(cmd->options);
	save = i;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			if (ft_strcmp(cmd->options[i],"-n") || i != 0)
				printf("%s ", cmd->options[i]);
			i++;
		}
	}
	printf("%s", parser_filter_quote(cmd->params));
	if (save)
		return ;
	printf("\n");
}
