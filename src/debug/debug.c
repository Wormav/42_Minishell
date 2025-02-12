/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:43:53 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/12 11:44:27 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m"


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

void print_content(char *content, t_ast *node ) {
    if (content == NULL) {
        printf(RESET);
        return;
    }

    if (node->token == TOKEN_CMD) {
        printf(RED "%s" RESET, content);
    } else if (node->token == TOKEN_PIPE) {
        printf(YELLOW "%s" RESET, content);
    } else {
        printf(BLUE "%s" RESET, content);
    }
}

void print_ast_recursive(t_ast *node, int level) {
	char *trim;

	trim = NULL;
	if (node == NULL)
		return;
    print_ast_recursive(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
	trim = ft_strtrim(node->content, " ");
	printf("[");
	print_content(trim, node);
    printf("]\n");
	lp_free(trim);
    print_ast_recursive(node->left, level + 1);
}

void print_tree(t_ast *ast)
{
	printf("\n==================== AST Tree ====================\n\n");
	print_ast_recursive(ast, 0);
	printf("\nLegend: ");
	printf(RED "cmd " RESET);
	printf(YELLOW "pipe " RESET);
	printf(BLUE "other" RESET);
	printf("\n================================================\n\n");
}

void print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;

	printf("\n================= Command Info =================\n");
	printf(RED "Command: [%s]\n" RESET, cmd->cmd ? cmd->cmd : "NULL");

	printf(YELLOW "Options: ");
	if (cmd->options)
	{
		for (int i = 0; cmd->options[i]; i++)
			printf("[%s] ", cmd->options[i]);
		printf("\n"RESET);
	}
	else
		printf("NULL\n");

	printf(BLUE "Parameters: [%s]\n" RESET, cmd->params ? cmd->params : "NULL");
	printf("\nLegend: ");
	printf(RED "cmd " RESET);
	printf(YELLOW "options " RESET);
	printf(BLUE "parameters \n" RESET);
	printf("=============================================\n\n");
}


void print_fds(t_fds *fds)
{
	printf("\n================= FD Info =================\n");
	if (!fds)
	{
		printf("No file descriptors\n");
		printf("==========================================\n\n");
		return;
	}

	while (fds)
	{
		printf("FD: [%s]\n", fds->fd_name ? fds->fd_name : "NULL");
		fds = fds->next;
	}
	printf("==========================================\n\n");
}

void print_data(t_data *data)
{
	printf("\n================= Data Info =================\n");
	if (!data)
	{
		printf("Data structure is NULL\n");
		printf("==========================================\n\n");
		return;
	}

	printf("Error parsing: %d\n", data->error_parsing);
	printf("Prompt string: %s\n", data->str_prompt ? data->str_prompt : "NULL");
	printf("Error code: %ld\n", data->error);
	printf("Error open flag: %s\n", data->flag_erropen ? "true" : "false");
	printf("Fork flag: %s\n", data->flag_fork ? "true" : "false");
	printf("==========================================\n\n");
}
