/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:26 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/31 12:42:25 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_handle_output(char *fd_trim, char *fd)
{
	int	output_fd;

	if (fd_trim)
	{
		output_fd = open(fd_trim, O_WRONLY | O_CREAT | define_macro(fd),
				0644);
		if (output_fd != -1)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
	}
}

static void	exec_handle_input(t_ast *ast)
{
	char	*input_file;
	int		input_fd;
	t_heredoc *heredoc;

	input_file = exec_identify_se(ast);
	if (input_file && !ft_strncmp(input_file, "<<", 2))
	{
			heredoc = handle_heredoc(ft_strtrim(input_file + 2, " "));
			if (heredoc)
			{
				input_fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (input_fd != -1)
				{
					write(input_fd, heredoc->content,
						ft_strlen(heredoc->content));
					close(input_fd);

					input_fd = open(".tmp", O_RDONLY);
					if (input_fd != -1)
					{
						dup2(input_fd, STDIN_FILENO);
						close(input_fd);
					}
				}
				lp_free(heredoc->content);
				lp_free(heredoc->delimiter);
				lp_free(heredoc);
				unlink(".tmp");
			}
	}
	else
	{
		input_file = exec_trim_fd(input_file);
			if (input_file)
			{
				input_fd = open(input_file, O_RDONLY);
				if (input_fd != -1)
				{
					dup2(input_fd, STDIN_FILENO);
					close(input_fd);
				}
				lp_free(input_file);
			}
	}
}

void	trunc_orders_fds(t_fds *fds)
{
	if (!fds)
		return ;
	while (fds)
	{
		if (!ft_strncmp(fds->fd_name, "> ", 2))
			open(ft_strtrim(fds->fd_name, "> "), O_TRUNC | O_CREAT);
		fds = fds->next;
	}
}

void	exec_ast(t_ast *ast, t_env *env_lst)
{
	int		stdin_backup;
	int		stdout_backup;
	t_fds	*fds;
	char	*fd_trim;
	char	*fd;

	fds = NULL;
	fd_trim = NULL;
	exec_setup_fds(ast, &fds, &fd, &fd_trim);
	if (!ast || !env_lst)
		return ;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	exec_handle_input(ast);
	exec_handle_output(fd_trim, fd);
	exec_ast_next(ast, env_lst);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	trunc_orders_fds(fds);
	exec_free_fds(fds);
}
