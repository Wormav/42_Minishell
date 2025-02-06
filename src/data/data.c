/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:25:09 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/06 14:38:00 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	data_add_fd_to_array(t_data *data, int fd)
{
	int	i;

	i = 0;
	while (i < ARR_FD_SIZE && data->arr_fd[i] != 0)
		i++;
	if (i < ARR_FD_SIZE)
		data->arr_fd[i] = fd;
}

void	data_close_all_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < ARR_FD_SIZE && data->arr_fd[i] != 0)
	{
		close(data->arr_fd[i]);
		data->arr_fd[i] = 0;
		i++;
	}
}

void	data_close_and_exit(t_data *data, long exit_code)
{
	int	i;

	i = 0;
	while (i < ARR_FD_SIZE && data->arr_fd[i] != 0)
	{
		close(data->arr_fd[i]);
		data->arr_fd[i] = 0;
		i++;
	}
	exit(exit_code);
}
