/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:43:53 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/11 15:17:43 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <ast.h>
#include <stdio.h>

static const char *token_to_string(int token) {
	switch (token) {
		case TOKEN_PIPE: return "TOKEN_PIPE";
		case TOKEN_REDIR_IN: return "TOKEN_REDIR_IN";
		case TOKEN_REDIR_OUT: return "TOKEN_REDIR_OUT";
		case TOKEN_HEREDOC: return "TOKEN_HEREDOC";
		case TOKEN_APPEND: return "TOKEN_APPEND";
		case TOKEN_QUOTE: return "TOKEN_QUOTE";
		case TOKEN_DQUOTE: return "TOKEN_DQUOTE";
		case TOKEN_L_PARENTHESIS: return "TOKEN_L_PARENTHESIS";
		case TOKEN_R_PARENTHESIS: return "TOKEN_R_PARENTHESIS";
		case TOKEN_VAR: return "TOKEN_VAR";
		case TOKEN_WAVE: return "TOKEN_WAVE";
		case TOKEN_WORD: return "TOKEN_WORD";
		case TOKEN_ARGS: return "TOKEN_ARGS";
		case TOKEN_DPIPE: return "TOKEN_DPIPE";
		case TOKEN_D_AND: return "TOKEN_DOUBLE_AND";
		case TOKEN_WILDCARD: return "TOKEN_WILDCARD";
		case TOKEN_FILE: return "TOKEN_FILE";
		case TOKEN_CMD: return "TOKEN_CMD";
		case TOKEN_LIMITER: return "TOKEN_LIMITER";
		case TOKEN_SPACE: return "TOKEN_SPACE";
		default: return "UNKNOWN_TOKEN";
	}
}

void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("Token content = %s\n", head->content);
		printf("%s\n", token_to_string(head->type));
		printf("index = %d || priority = %d\n", head->index, head->priority);
		head = head->next;
	}
}

static void print_content(const char *content)
{
    int i;
    int prev_space;

    i = 0;
    prev_space = 0;
    while (content && content[i])
    {
        if (content[i] == ' ')
        {
            if (!prev_space)
                printf(" ");
            prev_space = 1;
        }
        else
        {
            printf("%c", content[i]);
            prev_space = 0;
        }
        i++;
    }
}

void print_ast_recursive(t_ast *node, int level) {
	char *trim;

	trim = NULL;
	if (node == NULL)
		return;

    // Afficher d'abord la branche droite
    print_ast_recursive(node->right, level + 1);

    // Ajouter les espaces pour l'indentation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Afficher le nœud actuel
	trim = ft_strtrim(node->content, " ");
	printf("[");
	print_content(trim);
    printf("]\n");
	free(trim);

	// Afficher la branche gauche
    print_ast_recursive(node->left, level + 1);
}

void print_tree(t_ast *ast)
{
	printf("\n==================== AST Tree ====================\n\n");
	print_ast_recursive(ast, 0);
	printf("\n================================================\n\n");
}
