/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:59:04 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/11 20:05:31 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

char	*exec_trim_fd(char *fd)
{
	char	*trimmed;
	int		start;

	if (!fd)
		return (NULL);
	start = 0;
	while (fd[start] && (fd[start] == '>' || fd[start] == '<'))
		start++;
	trimmed = ft_strdup(fd + start);
	trimmed = ft_strtrim(trimmed, " \"'");
	return (trimmed);
}

int	define_macro(char *fd)
{
	if (!ft_strncmp(fd, ">>", 2))
		return (O_APPEND);
	else
		return (O_TRUNC);
}

void	exec_ast_next(t_ast *ast, t_env **env_lst, t_data *data)
{
	int		pipefd[2];
	int		flag_exit;

	flag_exit = 0;
	if (ast->parent && ast->parent->token == TOKEN_PIPE)
		flag_exit = 1;
	if (!ast)
		return ;
	while (ast && ast->token != TOKEN_CMD && ast->token != TOKEN_PIPE)
		ast = ast->left;
	if (!ast)
		return ;
	if (ast->token == TOKEN_PIPE)
		handle_pipe(ast, env_lst, pipefd, data);
	else if (ast->token == TOKEN_CMD)
		exec(ast, env_lst, &flag_exit, data);
}

void	exec_setup_fds(t_ast *ast, t_fds **fds, char **fd, t_data *data)
{
	*fd = exec_identify_fd(ast);
	if (*fd == NULL)
		return ;
	if (access(*fd, F_OK) == 0 && access(*fd, R_OK) != 0)
	{
		data->flag_erropen = true;
		data->error = 2;
		ft_printf(2, "minishell: %s: Permission denied\n", *fd);
		if (data->flag_fork)
			data_close_and_exit(data, data->error);
		return ;
	}
	exec_store_other_fds(ast, fds, *fd);
}

int	is_directory(const char *path)
{
	struct stat	file;

	if (stat(path, &file) == 0)
		return (S_ISDIR(file.st_mode));
	return (0);
}
