/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:04:31 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 21:07:11 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	putnbr_hex_fd(int fd, uint64_t nb, int flag)
{
	int	count;

	count = 0;
	if (flag == 1)
	{
		if (nb > 15)
			count += putnbr_hex_fd(fd, nb >> 4, flag);
		count += putchar_fd(fd, MAX_HEX[(nb & 0xF)]);
	}
	else if (flag == 0)
	{
		if (nb > 15)
			count += putnbr_hex_fd(fd, nb >> 4, flag);
		count += putchar_fd(fd, MIN_HEX[(nb & 0xF)]);
	}
	return (count);
}

int	putstr_fd(int fd, char *str)
{
	int	len;

	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	len = printf_strlen(str);
	write(fd, str, len);
	return (len);
}

int	print_pointer_fd(int fd, uintptr_t ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		count += putstr_fd(fd, "(nil)");
		return (count);
	}
	count += putstr_fd(fd, "0x");
	count += putnbr_hex_fd(fd, ptr, 0);
	return (count);
}

int	putnbr_fd(int fd, int nb)
{
	int	count;

	count = 0;
	if (nb == (1 << 31))
		return (putstr_fd(fd, MIN_INT));
	if (nb < 0)
	{
		count += putchar_fd(fd, '-');
		nb *= -1;
	}
	if (nb > 9)
	{
		count += putnbr_fd(fd, nb / 10);
		count += putnbr_fd(fd, nb % 10);
	}
	else
		count += putchar_fd(fd, nb + '0');
	return (count);
}
