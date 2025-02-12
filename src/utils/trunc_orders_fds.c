/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_orders_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:18:58 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/12 16:00:37 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void trunc_orders_fds(t_fds *fds, t_data *data)
{
    char *fd_trim;
    int fd;

    if (!fds)
        return;

    while (fds) {
        if (!ft_strncmp(fds->fd_name, "> ", 2)) {
            fd_trim = ft_strtrim(fds->fd_name, "> ");
            fd = open(fd_trim, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd != -1) {
                data_add_fd_to_array(data, fd);
            } else {
                if (access(fd_trim, F_OK) == 0 && access(fd_trim, W_OK) != 0) {
                    ft_printf(2, "minishell: %s: Permission denied\n", fd_trim);
                    data->error = 1;
                } else {
                    ft_printf(2, "minishell: %s: No such file or directory\n", fd_trim);
                    data->error = 1;
                }
                data->flag_erropen = true;
            }
            lp_free(fd_trim);
        }
        fds = fds->next;
    }
}
