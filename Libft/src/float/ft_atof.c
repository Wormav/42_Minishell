/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:14:15 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/19 12:56:14 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	check_point(char c, int *error, char *flag, int8_t *j)
{
	if (c == '.')
	{
		if (*flag == '1')
		{
			*error = 1;
			return (1);
		}
		*flag = '1';
		*j -= 1;
	}
	return (0);
}

double	ft_atof(char *nptr, int *error)
{
	double	value;
	char	flag;
	int8_t	j;
	int		sign;

	if (!nptr || !*nptr)
		return (0.000000);
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	value = 0.0;
	flag = '0';
	j = 0;
	while (*nptr)
	{
		if (check_point(*nptr, error, &flag, &j))
			return (0);
		value = value * 10 + (*nptr++) - '0';
	}
	return (value * pow(10, j) * sign);
}
