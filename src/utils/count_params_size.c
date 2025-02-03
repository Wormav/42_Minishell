/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_params_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:36 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/03 16:05:27 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_params_size(char *params)
{
	int		size;
	int		i;
	char	**param_array;

	size = 0;
	if (params)
	{
		param_array = ft_split(params, ' ');
		i = 0;
		while (param_array[i])
		{
			size++;
			i++;
		}
		free_split(param_array);
	}
	return (size);
}
