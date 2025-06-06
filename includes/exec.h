/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:07:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/14 08:40:52 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <ast.h>
# include <env.h>
# include <data.h>
# include <sys/stat.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**options;
	char	*params;
}	t_cmd;

typedef struct s_fds
{
	char			*fd_name;
	struct s_fds	*next;
}	t_fds;

typedef struct s_heredoc
{
	char	*delimiter;
	char	*content;
	int		flag_env;
}	t_heredoc;

// create cmd
t_cmd		*exec_create_cmd(char *str);
void		cleanup_cmd(t_cmd *cmd);

// identify fd
void		exec_store_other_fds(t_ast *ast, t_fds **list, char *main_fd);
char		*exec_identify_fd(t_ast *ast);
char		*exec_identify_se(t_ast *ast);
void		exec_free_fds(t_fds *fds, int stdin, int stdout);

// exec
void		exec(t_ast *ast, t_env **env_lst, int *flag_exit, t_data *data);
char		*find_cmd(t_cmd *cmd, t_env *env, long *error);
void		execute_child_process(char *cmd_name, char **argv_cmd,
				char **env_lst, t_cmd *cmd);

// execve
int			cmd_size(t_cmd *cmd);
void		fill_params_array(char **str, t_cmd *cmd, int *i);
char		**join_params(t_cmd *cmd);

//utils

int			skip_space(char *str);
int			find_next_size(char *str);
int			check_opts(char *str);
int			count_args(char *str);
int			find_first_size(char *str);

// exec ast
void		exec_ast(t_ast *ast, t_env **env_lst, t_data *data);
void		exec_ast_next(t_ast *ast, t_env **env_lst, t_data *data);
void		exec_handle_redir_in(char *input_file, t_data *data);

// exec ast utils
char		*exec_trim_fd(char *fd);
int			define_macro(char *fd);
void		exec_ast_next(t_ast *ast, t_env **env_lst, t_data *data);
void		exec_setup_fds(t_ast *ast, t_fds **fds, char **fd, t_data *data);
int			is_directory(const char *path);

// exec handle pipe
void		handle_pipe(t_ast *ast, t_env **env_lst, int pipefd[2],
				t_data *data);

// exec heredoc
t_heredoc	*handle_heredoc(char *delimiter);
void		free_heredoc(t_heredoc *heredoc);

// exec_error_fd
void		handle_output_error(char *fd, t_data *data);
void		check_fd_permissions(char *fd_trim, t_data *data);
void		exec_handle_output(char *fd_trim, char *fd, t_data *data);
void		exec_handle_redir_in(char *input_file, t_data *data);

// exec_others_commands.c
void		process_others_cmd(t_cmd *cmd, t_env **env_lst, t_data *data);

#endif
