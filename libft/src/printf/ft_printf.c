/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:06:47 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 21:01:20 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_string_parsing(int fd, va_list list, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += putchar_fd(fd, va_arg(list, int));
	if (c == 's')
		len += putstr_fd(fd, va_arg(list, char *));
	if (c == 'X' || c == 'x')
		len += putnbr_hex_fd(fd, va_arg(list, unsigned int), (c == 'X'));
	if (c == 'd')
		len += putnbr_fd(fd, va_arg(list, int));
	if (c == 'u')
		len += unlobby_fd(fd, va_arg(list, unsigned int));
	if (c == 'i')
		len += putnbr_fd(fd, va_arg(list, int));
	if (c == 'p')
		len += print_pointer_fd(fd, va_arg(list, uintptr_t));
	if (c == '%')
		len += putchar_fd(fd, '%');
	return (len);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		count;
	va_list	list;

	if (!str)
		return (-1);
	count = 0;
	va_start(list, str);
	while (*str)
	{
		if (*str == '%')
		{
			count += ft_string_parsing(fd, list, *(str + 1));
			str++;
		}
		else
			count += putchar_fd(fd, *str);
		str++;
	}
	va_end(list);
	return (count);
}
