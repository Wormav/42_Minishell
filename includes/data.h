/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:13:27 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/09 23:08:47 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define ARR_FD_SIZE 8192

# include <stdbool.h>

typedef struct s_data
{
	int		error_parsing;
	char	*str_prompt;
	long	error;
	int		arr_fd[ARR_FD_SIZE];
	bool	flag_erropen;
	bool	flag_fork;
}	t_data;

void	data_add_fd_to_array(t_data *data, int fd);
void	data_close_all_fd(t_data *data);
void	data_close_and_exit(t_data *data, long exit_code);

#endif
