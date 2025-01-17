/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/17 16:44:44 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <minishell.h>


/*main fonction env
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list	*lst = env_fill_list(envp);
	t_list	*tmp = lst;
	printf("Before Insert:\n");
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n\n");
	tmp = lst;
	env_list_insert(&lst, ft_lstnew("A=oui"));
	env_list_remove(&lst, "ALACRITTY_LO=");
	tmp = lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	env_list_free(&lst);
}

int    main(int argc, char **argv, char **env)
{
    t_cmd    cmd = {0};

     if (argc != 2)
         return (1);
    if (argc)
    {
        process_dev_cmd(argc, argv, &cmd, env);
         printf("cmd: %s\n", cmd.cmd);
         printf("options: %s\n", cmd.options[0]);
         printf("parmas: %s\n", cmd.params);
         for (int i = 0; cmd.env[i]; i++)
             printf("options[%d]: %s\n", i, cmd.env[i]);
    }
	int	error;
	char	*str = ft_echo(cmd, &error);
	printf(">>%s\n", str);
    free(cmd.cmd);
     for (int i = 0; cmd.options[i]; i++)
         free(cmd.options[i]);
     free(cmd.options);
     free(cmd.params);
}*/
// * main de base

static void	process_parsing(char *argv1)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;
	char 		*str;

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
	exec(ast);
	clean_memory(ast, list, str);
}

int	main(int argc, char **argv)
{
	if (argc > 2)
		return (1);
	process_parsing(argv[1]);
}

// * main de dev pour les CMD

// static void process_dev_cmd(int argc, char **argv, t_cmd *cmd, char **env)
// {
// 	cmd->cmd = ft_strdup(argv[1]);
// 	cmd->options = ft_split(argv[2], ' ');
// 	if (argc > 3)
// 		cmd->params = ft_strdup(argv[3]);
// }

// static void cleanup_cmd(t_cmd *cmd)
// {
//     if (cmd->cmd)
//         free(cmd->cmd);
//     if (cmd->options) {
//         for (int i = 0; cmd->options[i]; i++)
//             free(cmd->options[i]);
//         free(cmd->options);
//     }
//     if (cmd->params)
//         free(cmd->params);
// }

// // *main de pwd

// int main(int argc, char **argv, char **env)
// {
//     t_cmd cmd;
//     char *result;

//     ft_memset(&cmd, 0, sizeof(t_cmd));

//     if (argc)
//         process_dev_cmd(argc, argv, &cmd, env);

//     result = execute_pwd(&cmd); // test du pwd
//     if (result)
//     {
//         printf("%s", result);
//         free(result);
//     }
//     cleanup_cmd(&cmd);
//     return (0);
// }
