/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:17:21 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 22:19:43 by jlorette         ###   ########.fr       */
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

int	echo_count_option_n(char **options)
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
