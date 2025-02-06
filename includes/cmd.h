/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:29:14 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/06 14:35:43 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <exec.h>
# include <env.h>
# include <data.h>

void	execute_echo(t_cmd *cmd, t_env *env);
void	execute_pwd(t_cmd *cmd, t_data *data);
void	execute_unset(t_cmd *cmd, t_data *data, t_env **env_lst);
void	execute_cd(t_env *env, t_cmd *cmd, t_data *data);
void	execute_export(t_env **env, t_cmd *cmd, t_data *data);
void	execute_exit(t_cmd *cmd, t_data *data, int *flag_exit);
void	execute_env(t_env *env, t_cmd *cmd, t_data *data);
int		export_is_valid_key(char *str);
int		export_find_next_sign(char sign, char *str);
char	*export_remove_plus_before_equal(char *str);
void	export_process_args_with_equal(char *split, int valid_key, t_env **env);
void	export_process_args(char *split, t_data *data, t_env **env);
int		echo_count_option_n(char **options);
int		echo_check_dollar_sign(char *str);
char	*echo_process_status_exit(char *result, char *var_start, t_env *env);
char	*exit_trim_quote_first_option(char *str);

#endif
