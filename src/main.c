/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/14 18:23:41 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

 static void	process_parsing(char *argv1)
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
 	print_tree(ast);
 	clean_memory(ast, list, argv1);
}

int main(int argc, char **argv)
{
	(void)argc;
	process_parsing(ft_strdup(argv[1]));
}
/*
static void process_dev_cmd(char **argv, t_cmd *cmd, char **env)
{
	cmd->cmd = ft_strdup(argv[1]);
	cmd->options = ft_split(argv[2], ' ');
	cmd->params = ft_strdup(argv[3]);
	cmd->env = env;
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	cmd;

	// if (argc != 2)
	// 	return (1);
	if (argc)
	{
		process_dev_cmd(argv, &cmd, env);
		printf("cmd: %s\n", cmd.cmd);
		printf("options: %s\n", cmd.options[0]);
		printf("parmas: %s\n", cmd.params);
		for (int i = 0; cmd.env[i]; i++)
			printf("options[%d]: %s\n", i, cmd.env[i]);
	}


// code here

	free(cmd.cmd);
	for (int i = 0; cmd.options[i]; i++)
		free(cmd.options[i]);
	free(cmd.options);
	free(cmd.params);
}*/
