/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:54:56 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/07 13:03:06 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <token.h>

typedef struct	__attribute__((packed)) s_ast_node
{
	t_token				*token;
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

// TODO fonctions (toutes les noms commence par AST)

t_ast_node		*ast_add_node(t_token *type);
void			ast_free(t_ast_node *root);
t_ast_node		*ast_join(t_ast_node *left, t_ast_node *right, t_token *type);
// ast_count_levels (compte la profondeur max de l'abre)
// ast_create(utilise les token et add_node pour cree l abre)

#endif
