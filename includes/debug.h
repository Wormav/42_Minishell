/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:56:51 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/06 08:24:08 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <token.h>
# include <ast.h>
# include <exec.h>

typedef struct s_adress
{
	t_token				**address;
	struct s_address	*next;
}						t_address;

void	print_token_list(t_token *head);
void	print_tree(t_ast *ast);
void	print_cmd(t_cmd *cmd);
void	print_fds(t_fds *fds);

#endif
