/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/16 08:54:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// * main de base

static void cleanup_cmd(t_cmd *cmd)
{
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->options) {
        for (int i = 0; cmd->options[i]; i++)
            free(cmd->options[i]);
        free(cmd->options);
    }
    if (cmd->params)
	{
        free(cmd->params);
	}
	free(cmd);
}

static void	process_parsing(char *argv1)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;
	t_cmd		*cmd;
	char		*str;

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
	ast = ast_create(list, ast);
	print_tree(ast);
	cmd = exec_create_cmd(ast);
	print_cmd(cmd);
	cleanup_cmd(cmd);
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
