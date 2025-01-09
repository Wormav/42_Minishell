/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/09 19:15:49 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "ast.h"
#include <debug.h>
#include <parser.h>
#include <token.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*str;
	int		err = 0;
	t_token *list;
	t_ast *ast = NULL;

	if (argc != 2)
		return (1);
	str = ft_strdup(argv[1]);
	list = NULL;
	list = parse_string(str);
	err = parser_check(list);
	if (err)
	{
		token_identify_error(err);
		return (err);
	}
	list = parser_identify(list);
	parser_define_priority(&list);
	parser_join_tokens(list);
	ast = ast_create(list, ast);
	free_token(list);
	print_tree(ast);
	ast_free(ast);
	//print_token_list(list);
	free(str);
}
