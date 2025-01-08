/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/08 16:49:06 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "ast.h"
#include <debug.h>
#include <parser.h>
#include <token.h>
#include <stdio.h>

//* main de test du tokenizer

int	main(int argc, char **argv)
{
	char	*str;
	t_token	*list;
	int		err = 0;

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
	t_ast *ast = ast_create(list);
	print_tree(ast);
	free_token(list);
	free(str);
}
