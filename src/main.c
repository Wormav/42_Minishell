/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 10:06:42 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <debug.h>
#include <parser.h>
#include <token.h>

//* main de test du tokenizer

int	main(int argc, char **argv)
{
	char	*str;
	t_token	*list;

	if (argc != 2)
		return (1);
	str = ft_strdup(argv[1]);
	list = NULL;
	list = parse_string(str);
	//if (err)
	//	token_identify_error(err);
	list = parser_identify(list);
	print_token_list(list);
	free_token(list);
	free(str);
}

//* main de test de l'AST

/*int main(void)
{
	t_token test_token = {.content = NULL, .type = 2048, .next = NULL};

	t_ast_node *cmd = ast_add_node(&test_token);
	test_token.type = TOKEN_APPEND;
	t_ast_node *arg = ast_add_node(&test_token);
	test_token.type = 1;
	t_ast_node *pipe = ast_add_node(&test_token);
	test_token.type = 2048;
	t_ast_node *cmd2 = ast_add_node(&test_token);
	test_token.type = 4096;
	t_ast_node *arg2 = ast_add_node(&test_token);

	t_ast_node *cmd_args = ast_join(cmd, arg, &test_token);
	t_ast_node *cmd_args2 = ast_join(cmd2, arg2, &test_token);
	t_ast_node *root = ast_join(cmd_args, cmd_args2, &test_token);

	printf("AST created successfully\n");

	ast_print(root);

	free(pipe);
	ast_free(root);

	return (0);
}*/
