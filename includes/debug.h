/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:56:51 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/10 15:49:42 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <ast.h>
# include <token.h>

typedef struct s_adress
{
	t_token				**address;
	struct s_address	*next;
}						t_address;

void	print_token_list(t_token *head);
void	debug_print_tokens(t_token *head);
void	print_tree(t_ast *ast);
void	test_free(t_token **address, int flag);

#endif
