/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:20:31 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 17:30:00 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>

char	*ft_strsjoin(int size, char *start, ...)
{
	va_list	list;
	char	*str;
	char	*tmp;
	char	*next;

	str = start;
	va_start(list, start);
	tmp = str;
	while (--size)
	{
		next = va_arg(list, char *);
		str = ft_strjoin(str, next);
		if (!*str)
		{
			lp_free(tmp);
			break ;
		}
	}
	va_end(list);
	return (str);
}
