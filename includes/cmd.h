/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:29:14 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/20 14:38:58 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <exec.h>

char	*ft_echo(t_cmd cmd, int *error);
char	*execute_pwd(t_cmd *cmd, int *error);
char	*execute_unset(t_cmd *cmd, int *error, t_list *env_lst);
void	ft_cd(t_list *env, t_cmd *cmd, int *error);

#endif
