/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/12 16:14:39 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	echo_check_option_n(char *str)
{
	int	i;

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

static int	echo_count_option_n(char **options)
{
	int	count;
	int	i;

	if (!options)
		return (0);
	count = 0;
	i = 0;
	while (options[i] && echo_check_option_n(options[i]))
	{
		count++;
		i++;
	}
	return (count);
}

void	execute_echo(t_cmd *cmd, t_env *env)
{
	int	count_n;
	int	i;

	(void)env;
	i = echo_count_option_n(cmd->options);
	count_n = i;
	if (cmd->options)
	{
		while (cmd->options[i])
		{
			if (ft_strcmp(cmd->options[i], "-n") || i != 0)
				printf("%s ", cmd->options[i]);
			i++;
		}
	}
	printf("%s", parser_filter_quote(cmd->params));
	if (count_n)
		return ;
	printf("\n");
}
