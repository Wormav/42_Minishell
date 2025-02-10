/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:26 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/10 19:38:21 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <minishell.h>

static void	exec_handle_output(char *fd_trim, char *fd, t_data *data)
{
	int	output_fd;

	if (data->flag_erropen)
		return ;
	if (fd_trim)
	{
		output_fd = open(fd_trim, O_WRONLY | O_CREAT | define_macro(fd),
				0644);
		if (output_fd != -1)
		{
			dup2(output_fd, STDOUT_FILENO);
			data_add_fd_to_array(data, output_fd);
		}
	}
}

static void	exec_handle_input_heredoc(char *input_file, t_env **env,
int*input, t_data *data)
{
	t_heredoc	*heredoc;

	heredoc = handle_heredoc(ft_strtrim(input_file + 2, " "));
	if (heredoc)
	{
		*input = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*input != -1)
		{
			if (heredoc->flag_env)
				write(*input, env_replace_env_vars(*env, heredoc->content),
					ft_strlen(heredoc->content));
			else
				write(*input, heredoc->content,
					ft_strlen(heredoc->content));
			close(*input);
			*input = open(".tmp", O_RDONLY);
			if (*input != -1)
			{
				dup2(*input, STDIN_FILENO);
				data_add_fd_to_array(data, *input);
			}
		}
		free_heredoc(heredoc);
		unlink(".tmp");
	}
}

static void	exec_handle_input(t_ast *ast, t_env **env, t_data *data)
{
	char	*input_file;
	int		input_fd;

	input_file = exec_identify_se(ast);
	if (input_file && !ft_strncmp(input_file, "<<", 2))
		exec_handle_input_heredoc(input_file, env, &input_fd, data);
	else if (input_file && !ft_strncmp(input_file, "<", 1))
		exec_handle_redir_in(parser_filter_quote(input_file), data);
	else
	{
		input_file = exec_trim_fd(input_file);
		if (input_file)
		{
			input_fd = open(input_file, O_RDONLY);
			if (input_fd != -1)
			{
				dup2(input_fd, STDIN_FILENO);
				data_add_fd_to_array(data, input_fd);
			}
			lp_free(input_file);
		}
	}
}

void	exec_handle_redir_in(char *input_file, t_data *data)
{
    if (!input_file)
        return;
    char *trim = ft_strtrim(input_file, " <");
    if (!trim)
        return;
    int input_fd = open(trim, O_RDONLY);
    if (input_fd == -1)
    {
        if (access(trim, F_OK) == 0 && access(trim, R_OK) != 0)
        {
            ft_printf(2, "minishell: %s: Permission denied\n", trim);
			if (data->flag_fork)
			data_close_and_exit(data, data->error);
            data->error = 2;
        }
        else
        {
            ft_printf(2, "minishell: %s: No such file or directory\n", trim);
            data->error = 1;
			if (data->flag_fork)
				data_close_and_exit(data, data->error);
        }
        data->flag_erropen = true;
        lp_free(trim);
        return;
    }
    data_add_fd_to_array(data, input_fd);
    dup2(input_fd, STDIN_FILENO);
    lp_free(trim);
}

void	check_fds(t_fds *fds, char *fd, t_data *data)
{
	char *fd_trim;

	if (data->flag_erropen || !fd)
		return ;
	fd_trim = exec_trim_fd(fd);
	if (access(fd_trim, F_OK) == 0 && access(fd_trim, R_OK) != 0)
	{
		ft_printf(2, "minishell: %s: Permission denied\n", fd_trim);
		if (data->flag_fork)
			data_close_and_exit(data, data->error);
		data->flag_erropen = true;
		data->error = 2;
		return ;
	}
	while (fds)
	{
		if (access(fds->fd_name, F_OK) == 0 && access(fds->fd_name, R_OK) != 0)
		{
			ft_printf(2, "minishell: %s: Permission denied\n", fds->fd_name);
			data->flag_erropen = true;
			data->error = 2;
			if (data->flag_fork)
				data_close_and_exit(data, data->error);
			break ;
		}
		fds = fds->next;
	}
}

void	exec_ast(t_ast *ast, t_env **env_lst, t_data *data)
{
	int		stdin_backup;
	int		stdout_backup;
	t_fds	*fds;
	char	*fd_trim;
	char	*fd;

	fds = NULL;
	fd_trim = NULL;
	fd = NULL;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	data_add_fd_to_array(data, stdin_backup);
	data_add_fd_to_array(data, stdout_backup);
	if (!ast || !env_lst)
		return ;
	exec_setup_fds(ast, &fds, &fd, data);
	fd_trim = exec_trim_fd(fd);
	check_fds(fds, fd, data);
	exec_handle_input(ast, env_lst, data);
	exec_handle_output(fd_trim, fd, data);
	exec_ast_next(ast, env_lst, data);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	trunc_orders_fds(fds, data);
	exec_free_fds(fds);
}
