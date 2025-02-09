/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_orders_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:18:58 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 23:19:25 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	trunc_orders_fds(t_fds *fds, t_data *data)
{
	char	*fd_trim;
	int		fd;

	if (!fds)
		return ;
	while (fds)
	{
		if (!ft_strncmp(fds->fd_name, "> ", 2))
		{
			fd_trim = ft_strtrim(fds->fd_name, "> ");
			fd = open(fd_trim, O_TRUNC | O_CREAT);
			if (fd != -1)
				data_add_fd_to_array(data, fd);
		}
		fds = fds->next;
	}
}
