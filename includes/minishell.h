/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:19:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/30 15:00:07 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <env.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# include <ast.h>
# include <debug.h>
# include <parser.h>
# include <token.h>
# include <stdio.h>
# include <error.h>
# include <utils.h>
# include <cmd.h>
# include <exec.h>

#endif
