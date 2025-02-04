/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:50:42 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 21:07:36 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int	printf_strlen(char *str)
{
	char	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}
