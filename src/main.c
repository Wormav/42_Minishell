/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/20 11:31:21 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <minishell.h>

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_list	*lst = env_fill_list(envp);
// 	t_list	*tmp = lst;
// 	printf("Before Insert:\n");
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\n\n");
// 	tmp = lst;
// 	env_list_insert(&lst, ft_lstnew("A=oui"));
// 	env_list_remove(&lst, "ALACRITTY_LO=");
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	env_list_free(&lst);
// }


static void	process_parsing(char *argv1, char **env)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;
	char 		*str;
	t_list	*env_lst = env_fill_list(env);

	str = ft_strdup(argv1);
	ast = NULL;
	list = token_parse_string(str);
	check_unsupported_char(list, &err);
	if (err)
		parser_identify_error(err, list, str);
	err = parser_check(list);
	if (err)
		token_identify_error(err, list, str);
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
