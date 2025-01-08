/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:54:56 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/08 16:03:04 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <token.h>

typedef struct	__attribute__((packed)) s_ast
{
	t_token			*token;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// TODO fonctions (toutes les noms commence par AST)

t_ast	*ast_node_init(t_token *token);
void	ast_push(t_ast **ast, t_ast *node);
t_ast	*ast_create(t_token *lst);

void	ast_free(t_ast *ast);
t_ast	*ast_join(t_ast *left, t_ast *right, t_token *type);
// ast_count_levels (compte la profondeur max de l'abre)
// ast_create(utilise les token et add_node pour cree l abre)

#endif
