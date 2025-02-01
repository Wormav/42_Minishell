/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:17:21 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/01 17:22:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo_check_dollar_sign(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

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
