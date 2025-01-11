/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/11 09:35:06 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	char		*str;
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;

	if (argc != 2)
		return (1);
	str = ft_strtrim(argv[1], " ");
	ast = NULL;
	list = token_parse_string(str);
	check_unsupported_char(list, &err);
	if (err)
		parser_identify_error(err, list, str);
	err = parser_check(list);
	if (err)
		token_identify_error(err, list, str);
	//print_token_list(list);
	list = parser_identify(list);
	parser_define_priority(&list);
	parser_join_tokens(list);
	ast = ast_create(list, ast);
	print_tree(ast);
	print_token_list(list);
	ast_free(ast);
	free_token(list);
	free(str);
}
