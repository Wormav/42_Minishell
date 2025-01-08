/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:56:51 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/08 10:49:56 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <token.h>
# include <ast.h>

void	print_token_list(t_token *head);
void	ast_print(t_ast_node *root);
void debug_print_tokens(t_token *head);

#endif
