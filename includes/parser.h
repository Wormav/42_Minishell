/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:37:29 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/09 22:20:38 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <token.h>
# include <data.h>
# include <env.h>

enum				e_token_error
{
	ERR_ODD_QUOTE = 1,
	ERR_ODD_DQUOTE,
	ERR_ODD_PARENTHESIS,
};

enum	e_error_syntax
{
	ERR_SYNTAX_PIPE = 0b001,
	ERR_SYNTAX_REDIR = 0b010,
	ERR_SYNTAX_UNEXPECTED = 0b01001,
};

enum				e_priority
{
	P_OUT_OR_APP_OR_PIPE_OR_HEREDOC = 1,
	P_PARENTHESIS,
	P_DOUBLEAND,
	P_TOKENS,
	P_CMDS,
	P_WORD
};

enum				e_parser
{
	PARSER_FILE,
	PARSER_CMD,
	PARSER_STRING
};

typedef struct s_parser
{
	int				index;
	char			*content;
	struct s_parser	*next;
}					t_parser;

int					parser_check(t_token *lst);
t_token				*parser_identify(t_token *list);
void				parser_define_priority(t_token **list);
t_token				*parser_join_tokens(t_token *list);
t_token				*parser_dquotes(t_token *list);
t_token				*parser_quotes_dquotes(t_token *list);
int					join_tokens_quotes(t_token *current);
t_token				*parser_join_word_and_cmd(t_token *list, int flag_heredoc);
t_token				*parser_join_redir_and_file(t_token *list);
t_token				*parser_join_heredoc_and_file(t_token *list);
t_token				*parser_join_file_and_redir_in(t_token *list);
void				set_next_file_with_spaces(t_token *lst);
void				set_next_cmd_with_spaces(t_token *lst);
char				*parser_filter_quote(char *str);
void				parser_errors_syntax(t_token *lst, long *error, int *err);
int					cmd_content_only_space(t_token *node);
void				parser_expand_var_env(t_data *data, t_env *env);
int					parser_check_dollar_sign(char *str);
char				*parser_process_status_exit(char *result, char *var_start, t_env *env);

#endif
