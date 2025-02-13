/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/13 12:09:04 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define PROMPT "minishell > "

int ack = 0;

void __handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
    if (ack != 42)
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
        ack = 130;
}

static void	process_parsing(char *prompt, t_env **env_lst, t_data *data)
{
	t_token		*list;
	t_ast		*ast;

	if (ack == 130)
    {
        data->error = 130;
        ack = 0;
	}
	save_return_val(data, env_lst);
	data_init(data);
	data->str_prompt = ft_strdup(prompt);
	ast = NULL;
	parser_expand_var_env(data, *env_lst);
	check_odd_quotes(data->str_prompt, &data->error_parsing);
	if (data->error_parsing)
		return (lp_free(data->str_prompt));
	list = token_parse_string(data->str_prompt);
	check_unsupported_char(list, &data->error_parsing);
	if (data->error_parsing)
	{
		parser_identify_error(data->error_parsing, list, data->str_prompt);
		return ;
	}
	data->error_parsing = parser_check(list);
	if (data->error_parsing)
		token_identify_error(data, list);
	parser_errors_syntax(list, &data->error, &data->error_parsing);
	if (data->error_parsing)
	{
		save_return_val(data, env_lst);
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
	exec_ast(ast, env_lst, data);
	clean_memory(ast, list, data->str_prompt);
}

int main(__attribute__((unused))int argc,
        __attribute__((unused))char **argv, char **envp)
{
    char    *str;
    static  t_data data = {0};
    struct sigaction sa;
    t_env *env_lst;

    data_init(&data);
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = __handle_sigint;
    env_lst = env_fill_list(envp);
    env_list_insert(&env_lst, env_lstnew("?=\"0\""));
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
    using_history();
    str = readline(PROMPT);
    while (str)
    {
        if (!*str)
        {
            free(str);
            str = readline(PROMPT);
            continue;
        }
        add_history(str);
        process_parsing(str, &env_lst, &data);
        free(str);
        str = readline(PROMPT);
    }
    clear_history();
    if (str)
        free(str);
    rl_clear_history();
    return (0);
}
