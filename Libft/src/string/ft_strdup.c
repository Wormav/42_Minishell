/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:51:56 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/19 15:17:26 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;

	size = ft_strlen(s);
	str = lp_alloc(size + 1 * sizeof(char));
	ft_strlcpy(str, s, size + 1);
	return (str);
}
