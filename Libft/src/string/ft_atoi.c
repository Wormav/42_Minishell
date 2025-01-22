/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:23:50 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/18 10:41:20 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	int			num;
	const char	*tmp;

	sign = 1;
	num = 0;
	tmp = nptr;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '-' || *tmp == '+')
	{
		if (*tmp == '-')
			sign *= -1;
		tmp++;
	}
	while (ft_isdigit(*tmp))
		num = num * 10 + (*tmp++ - '0');
	return (num * sign);
}
