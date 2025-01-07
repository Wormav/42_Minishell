/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/07 21:32:52 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
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
	printf("--------before before before---------\n");
	print_token_list(list);
	list = parser_identify(list);
	printf("--------before before---------\n");
	print_token_list(list);
	parser_define_priority(&list);
	printf("--------before---------\n");
	print_token_list(list);
	parser_join_tokens(list);
	printf("---------after----------\n");
	print_token_list(list);
	free_token(list);
	free(str);
}
