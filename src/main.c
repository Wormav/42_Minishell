/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/21 14:44:42 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <minishell.h>

static void	process_parsing(char *argv1, char **env)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;
	char 		*str;

	str = ft_strdup(argv1);
	ast = NULL;
	check_odd_quotes(str, &err);
	if (err)
		return (free(str));
	list = token_parse_string(str);
	check_unsupported_char(list, &err);
	if (err)
		parser_identify_error(err, list, str);
	err = parser_check(list);
	if (err)
		token_identify_error(err, list, str);
	t_list	*env_lst = env_fill_list(env);
	list = parser_identify(list);
	parser_define_priority(&list);
	print_token_list(list);
	parser_join_tokens(list);
	print_token_list(list);
	ast = ast_create(list, ast);
	print_tree(ast);
	exec(ast, env_lst);
	clean_memory(ast, list, str);
	env_list_free(&env_lst);
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 2)
		return (1);
	process_parsing(argv[1], env);
}
