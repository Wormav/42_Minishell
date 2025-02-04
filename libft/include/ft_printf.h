/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:15:22 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 21:09:33 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MIN_HEX	"0123456789abcdef"
# define MAX_HEX	"0123456789ABCDEF"
# define MIN_INT	"-2147483648"

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(
			int fd, const char *str, ...)__attribute__((format(printf, 2, 3)));
int		putnbr_fd(int fd, int nb);
int		putchar_fd(int fd, char c);
int		putnbr_hex_fd(int fd, uint64_t nb, int flag);
int		putstr_fd(int fd, char *str);
void	putunbr_fd(int fd, unsigned int nb);
int		unlobby_fd(int fd, unsigned int nb);
int		print_pointer_fd(int fd, uintptr_t ptr);
int		printf_strlen(char *str);

#endif
