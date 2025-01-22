/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:07:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:51:39 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <ast.h>
# include <env.h>

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

// create cmd
t_cmd	*exec_create_cmd(char *str);
void	cleanup_cmd(t_cmd *cmd);

// identify fd
void	exec_store_other_fds(t_ast *ast, t_fds **list, char *main_fd);
char	*exec_identify_fd(t_ast *ast);
void	exec_free_fds(t_fds *fds);

// exec
void	exec(t_ast *ast, t_env *env_lst);

//utils

int		skip_space(char *str);
int		find_next_size(char *str);
int		check_opts(char *str);
int		count_args(char *str);
int		find_first_size(char *str);

#endif
