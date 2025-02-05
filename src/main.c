/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/05 19:44:54 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

#define PROMPT "minishell > "

void	__handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ack = 127;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	process_parsing(char *argv1, t_env **env_lst)
{
	static int	err = 0;
	t_token		*list;
	t_ast		*ast;
	char 		*str;
	static long	error = 0;

	str = ft_strdup(argv1);
	ast = NULL;
	check_odd_quotes(str, &err);
	if (err)
		return (lp_free(str));
	list = token_parse_string(str);
	check_unsupported_char(list, &err);
	if (err)
	{
		parser_identify_error(err, list, str);
		return ;
	}
	err = parser_check(list);
	if (err)
		token_identify_error(err, list, str);
	parser_errors_syntax(list, &error, &err);
	if (err)
	{
		save_return_val(&error, env_lst);
		return;
	}
	list = parser_identify(list);
	parser_define_priority(&list);
//	printf("\n\n");
//	print_token_list(list);
	parser_join_tokens(list);
//	print_token_list(list);
	ast = ast_create(list, ast);
//	print_tree(ast);
	exec_ast(ast, env_lst, &error);
	clean_memory(ast, list, str);
}

int	main(__attribute__((unused))int argc,
		__attribute__((unused))char **argv, char **envp)
{
	char	*str;

	struct sigaction	sa;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = __handle_sigint;
	t_env	*env_lst = env_fill_list(envp);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	str = readline(PROMPT);
	while (str)
	{
		if (!*str)
		{
			str = readline(PROMPT);
			continue ;
		}
		add_history(str);
		process_parsing(str, &env_lst);
		free(str);
		str = readline(PROMPT);
	}
	rl_clear_history();
    return (0);
}
