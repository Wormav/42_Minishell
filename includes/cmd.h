/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:29:14 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 07:34:01 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <exec.h>
# include <env.h>

void 	ft_echo(t_cmd *cmd, int *error,t_env *env);
char 	*execute_pwd(t_cmd *cmd, int *error);
char	*execute_unset(t_cmd *cmd, int *error, t_env *env_lst);
void	ft_cd(t_env *env, t_cmd *cmd, int *error);
void	ft_export(t_env **env, t_cmd *cmd, int *error);
char	*execute_exit(t_cmd *cmd);
char	*execute_env(t_env *env, t_cmd *cmd, int *error);
int		export_is_valid_key(char *str);
int		export_check_params(char *str);
int		export_find_next_sign(char sign, char *str);
char	*export_remove_plus_before_equal(char *str);
void	export_process_args_with_equal(char *split, int valid_key, t_env **env);
void	export_process_args(char *split, int *error, t_env **env);

#endif
