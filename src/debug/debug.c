/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:43:53 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 10:14:49 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <ast.h>

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
		default: return "UNKNOWN_TOKEN";
	}
}

void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("Token content = %s\n", head->content);
		printf("%s\n", token_to_string(head->type));
		head = head->next;
	}
}

void    ast_print(t_ast_node *root)
{
    if (!root)
        return ;
    if (root->parent != NULL)
        printf("(%s) -> %s\n", token_to_string(root->parent->type.type),
               token_to_string(root->type.type));
    else
        printf("ROOT -> %s\n", token_to_string(root->type.type));
    if (root->left != NULL)
        ast_print(root->left);
    if (root->right != NULL)
        ast_print(root->right);
}
