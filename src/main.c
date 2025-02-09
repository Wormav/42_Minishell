/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/09 17:49:29 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define PROMPT "minishell > "

void	__handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// ack = 127;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void expand_var_env(t_data *data, t_env *env)
{
	char *result;
	char *str;
	int i;
	int j;
	int in_single_quotes;

	if (!data->str_prompt)
		return;

	str = data->str_prompt;
	result = lp_alloc((strlen(str) * 4 + 1) * sizeof(char));
	if (!result)
		return;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quotes = !in_single_quotes;

		if (!in_single_quotes && str[i] == '$' && str[i + 1] == '?')
		{
			char *exit_value = env_get_value(env, "$?");
			if (exit_value)
			{
				size_t len = ft_strlen(exit_value);
				ft_strlcat(result, exit_value, j + len + 1);
				j += len;
			}
			i += 2;
		}
		else if (!in_single_quotes && str[i] == '$' && (isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			int var_len = 1;
			while (isalnum(str[i + var_len]) || str[i + var_len] == '_')
				var_len++;

			char *var_name = ft_substr(str + i, 0, var_len);
			char *value = env_get_value(env, var_name);
			lp_free(var_name);

			if (value)
			{
				size_t len = ft_strlen(value);
				ft_strlcat(result, value, j + len + 1);
				j += len;
			}
			i += var_len;
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';

	lp_free(data->str_prompt);
	data->str_prompt = result;
}

static void	process_parsing(char *argv1, t_env **env_lst)
{
	static	t_data data = {0};
	t_token		*list;
	t_ast		*ast;

	save_return_val(&data, env_lst);
	data.str_prompt = ft_strdup(argv1);
	ast = NULL;
	expand_var_env(&data, *env_lst);
	check_odd_quotes(data.str_prompt, &data.error_parsing);
	if (data.error_parsing)
		return (lp_free(data.str_prompt));
	list = token_parse_string(data.str_prompt);
	check_unsupported_char(list, &data.error_parsing);
	if (data.error_parsing)
	{
		parser_identify_error(data.error_parsing, list, data.str_prompt);
		return ;
	}
	data.error_parsing = parser_check(list);
	if (data.error_parsing)
		token_identify_error(&data, list);
	parser_errors_syntax(list, &data.error, &data.error_parsing);
	if (data.error_parsing)
	{
		save_return_val(&data, env_lst);
		return;
	}
	list = parser_identify(list);
	parser_define_priority(&list);
	parser_join_tokens(list);
	ast = ast_create(list, ast);
#ifdef DEBUG
	#if DEBUG == 1
		printf("debug activate\n");
		print_token_list(list);
		print_tree(ast);
		print_token_list(list);
#endif
#endif
	exec_ast(ast, env_lst, &data);
	clean_memory(ast, list, data.str_prompt);
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
