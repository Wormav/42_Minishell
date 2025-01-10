/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:37:29 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/10 17:48:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>

enum				e_token_error
{
	ERR_ODD_QUOTE = 1,
	ERR_ODD_DQUOTE,
	ERR_ODD_PARENTHESIS
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

#endif
