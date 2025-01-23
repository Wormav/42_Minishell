/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:04:30 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/23 17:52:56 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <limits.h>

static long	convert_to_number(const char *tmp, int sign, int *overflow_error)
{
	long	num;
	long	prev;

	num = 0;
	while (*tmp >= '0' && *tmp <= '9')
	{
		prev = num;
		num = num * 10 + (*tmp++ - '0');
		if (num < prev
			|| (sign == 1 && num > LONG_MAX)
			|| (sign == -1 && - num < LONG_MIN))
		{
			*overflow_error = 1;
			return (0);
		}
	}
	return (num * sign);
}

long	ft_atol(char *nptr, int *overflow_error)
{
	int			sign;
	const char	*tmp;

	*overflow_error = 0;
	if (!nptr)
		return (0);
	sign = 1;
	tmp = nptr;
	while (*tmp == ' ' || (*tmp >= '\t' && *tmp <= '\r'))
		tmp++;
	if (*tmp == '-' || *tmp == '+')
		sign = 44 - *tmp++;
	return (convert_to_number(tmp, sign, overflow_error));
}
