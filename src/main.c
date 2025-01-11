/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/11 15:09:29 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process(char *argv1)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;

	ast = NULL;
	list = token_parse_string(argv1);
	check_unsupported_char(list, &err);
	if (err)
		parser_identify_error(err, list, argv1);
	err = parser_check(list);
	if (err)
		token_identify_error(err, list, argv1);
	list = parser_identify(list);
	parser_define_priority(&list);
	parser_join_tokens(list);
	ast = ast_create(list, ast);
	//print_tree(ast);
	clean_memory(ast, list, argv1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	process(ft_strtrim(argv[1], " "));
}
