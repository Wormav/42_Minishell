/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/21 11:52:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_ack = 0;

static void	process_parsing_init(char *prompt, t_env **env_lst, t_data *data)
{
	if (g_ack == 130 || g_ack == 131)
	{
		data->error = g_ack;
		g_ack = 0;
	}
	save_return_val(data, env_lst);
	data_init(data);
	data->str_prompt = ft_strdup(prompt);
	parser_expand_var_env(data, *env_lst);
	check_odd_quotes(data->str_prompt, &data->error_parsing);
	if (data->error_parsing)
		token_identify_error(data, NULL);
}

static void	process_parsing_checks(t_token *list, t_data *data, t_env **env_lst)
{
	data->error_parsing = parser_check(list);
	if (data->error_parsing)
		token_identify_error(data, list);
	parser_errors_syntax(list, &data->error, &data->error_parsing);
	if (data->error_parsing)
	{
		save_return_val(data, env_lst);
		return ;
	}
	list = parser_identify(list);
	parser_define_priority(&list);
	parser_join_tokens(list);
}

static void	process_parsing(char *prompt, t_env **env_lst, t_data *data)
{
	t_token	*list;
	t_ast	*ast;

	ast = NULL;
	process_parsing_init(prompt, env_lst, data);
	if (data->error_parsing)
		return ;
	list = token_parse_string(data->str_prompt);
	check_unsupported_char(list, &data->error_parsing);
	if (data->error_parsing)
	{
		parser_identify_error(data->error_parsing, list, data->str_prompt);
		return ;
	}
	process_parsing_checks(list, data, env_lst);
	if (data->error_parsing)
		return ;
	ast = ast_create(list, ast);
	exec_ast(ast, env_lst, data);
	clean_memory(ast, list, data->str_prompt);
}

static void	process_readline(char **prompt, t_env **env_lst, t_data *data)
{
	*prompt = readline(PROMPT);
	while (*prompt)
	{
		if (!**prompt)
		{
			free(*prompt);
			*prompt = readline(PROMPT);
			continue ;
		}
		add_history(*prompt);
		process_parsing(*prompt, env_lst, data);
		free(*prompt);
		*prompt = readline(PROMPT);
	}
}

int	main(__attribute__((unused))int argc,
__attribute__((unused))char **argv, char **envp)
{
	static t_data		data = {0};
	struct sigaction	sa;
	t_env				*env_lst;
	char				*str;

	data_init(&data);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	env_lst = env_fill_list(envp);
	env_list_insert(&env_lst, env_lstnew("?=\"0\""));
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	process_readline(&str, &env_lst, &data);
	printf("exit\n");
	clear_history();
	if (str)
		free(str);
	rl_clear_history();
	return (0);
}
