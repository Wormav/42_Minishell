/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:39:52 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/19 12:57:32 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int	check_point(char **str, int *divisor, int *error)
{
	static int	flag = 0;

	if (**str == '.' && flag)
	{
		*error = 1;
		return (1);
	}
	if (**str == '.')
	{
		*str += 1;
		flag = 1;
		*divisor -= 1;
	}
	if (!ft_isdigit(**str))
		*error = 1;
	return (0);
}

float	ft_strtof(char *nptr, char **remain, int *error)
{
	float	value;
	int		divisor;
	int		sign;

	value = 0;
	divisor = 0;
	if (!nptr)
		return (0);
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	sign = (*nptr != '-') - (*nptr == '-');
	nptr += (*nptr && (*nptr == '-' || *nptr == '+'));
	while (*nptr)
	{
		if (check_point(&nptr, &divisor, error))
			return (0);
		else if (divisor < 0)
			divisor--;
		value = value * 10.0f + *nptr++ - '0';
	}
	if (remain)
		*remain = nptr;
	return (value * pow(10, divisor + 1) * sign);
}
