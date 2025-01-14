/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:29:14 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/14 20:39:25 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_cmd
{
	char	*cmd;
	char	**options;
	char	*params;
	char	**env;
}	t_cmd;

char	*execute_pwd(t_cmd *command);

#endif
