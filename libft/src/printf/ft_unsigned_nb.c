/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:41:50 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 21:02:53 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	unsize(unsigned int nb)
{
	int	count;

	count = 0;
	if (!nb)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

void	putunbr_fd(int fd, unsigned int nb)
{
	if (nb > 9)
	{
		putunbr_fd(fd, nb / 10);
		putunbr_fd(fd, nb % 10);
	}
	else
		putchar_fd(fd, nb + '0');
}

int	unlobby_fd(int fd, unsigned int nb)
{
	int	count;

	count = 0;
	putunbr_fd(fd, nb);
	count += unsize(nb);
	return (count);
}
