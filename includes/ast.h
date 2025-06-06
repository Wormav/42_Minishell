/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:54:56 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:47:18 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <token.h>
# include <ast.h>

typedef struct s_ast
{
	char			*content;
	int				priority;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				token;

}					t_ast;

t_ast				*ast_node_init(t_token *token);
t_token				*ast_find_lowest_priority_token(t_token *list);
t_ast				*ast_create(t_token *lst, t_ast *root);
void				ast_split_token_list(t_token *list, t_token *lowest,
						t_token **left, t_token **right);
void				ast_free(t_ast *ast);

#endif
