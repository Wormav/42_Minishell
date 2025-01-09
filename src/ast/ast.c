/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:42:50 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/09 18:59:51 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <stdlib.h>
#include <token.h>

void cleanup_token_list(t_token **token) {
    t_token *current;
    t_token *next;

    if (!token || !*token)
        return;

    current = *token;
    while (current) {
        next = current->next; // Sauvegarder le pointeur vers le prochain nœud
        if (current->content)
            free(current->content); // Libérer le contenu
        free(current);              // Libérer le nœud
        current = next;             // Passer au suivant
    }

    *token = NULL; // S'assurer que le pointeur d'origine est nul après la libération
}


void relink(t_token *node) {
    t_token *free_node;

    if (!node || !node->next)
        return; // Rien à relier si `node` ou `node->next` est NULL

    free_node = node->next; // Sauvegarde du nœud à libérer
    node->next = free_node->next; // Relier le nœud actuel à celui après `free_node`
	free(node->content);
	free(free_node); // Libérer le nœud intercalé
}


t_ast	*ast_create(t_token *lst, t_ast *root)
{
	t_token *left __attribute__((cleanup(cleanup_token_list)));
	t_token *right __attribute__((cleanup(cleanup_token_list)));
    t_token *lowest;

	left = NULL;
	right = NULL;

	if (!lst)
		return (NULL);
    lowest = ast_find_lowest_priority_token(lst);
    if (!lowest)
        return (NULL);
    root = ast_node_init(lowest);
    if (token_listsize(lst) == 0)
        return (NULL);

    ast_split_token_list(lst, lowest, &left, &right);

	if (root && token_listsize(lst) > 1)
    {
		root->left = ast_create(left, root->left);
		root->right = ast_create(right, root->right);
		// ! zero leak mais segfault
	}
	return (root);
}
