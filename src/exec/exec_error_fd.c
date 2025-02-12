/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:03:00 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/12 18:34:05 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_output_error(char *fd, t_data *data)
{
	if (access(fd, F_OK) == 0 && access(fd, R_OK) != 0)
	{
		ft_printf(2, "minishell: %s: Permission denied\n", fd);
		data->error = 1;
	}
	else
	{
		ft_printf(2, "minishell: %s: No such file or directory\n", fd);
		data->error = 1;
	}
	data->flag_erropen = true;
}

void	check_fd_permissions(char *fd_trim, t_data *data)
{
	if (access(fd_trim, F_OK) == 0 && access(fd_trim, R_OK) != 0)
	{
		ft_printf(2, "minishell: %s: Permission denied\n", fd_trim);
		if (data->flag_fork)
			data_close_and_exit(data, data->error);
		data->flag_erropen = true;
		data->error = 1;
	}
}

void	exec_handle_output(char *fd_trim, char *fd, t_data *data)
{
	int	output_fd;

	if (data->flag_erropen)
		return ;
	if (fd_trim)
	{
		output_fd = open(fd_trim, O_WRONLY | O_CREAT | define_macro(fd), 0644);
		if (output_fd != -1)
		{
			dup2(output_fd, STDOUT_FILENO);
			data_add_fd_to_array(data, output_fd);
		}
		else
		{
			handle_output_error(fd, data);
			return ;
		}
	}
}

void	exec_handle_redir_in(char *input_file, t_data *data)
{
	char	*trim;
	int		input_fd;

	trim = ft_strtrim(input_file, " <");
	input_fd = open(trim, O_RDONLY);
	if (!input_file || !trim)
		return ;
	data->flag_redir_in = true;
	if (input_fd == -1)
	{
		if (access(trim, F_OK) == 0 && access(trim, R_OK) != 0)
		{
			ft_printf(2, "minishell: %s: Permission denied\n", trim);
			data->error = 1;
		}
		else
		{
			ft_printf(2, "minishell: %s: No such file or directory\n", trim);
			data->error = 1;
		}
		data->flag_erropen = true;
		return ;
	}
	data_add_fd_to_array(data, input_fd);
	dup2(input_fd, STDIN_FILENO);
}
