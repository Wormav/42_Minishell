/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:49:56 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/08 10:37:58 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/include/libft.h"
# include <stdint.h>

enum	e_token
{
	TOKEN_PIPE = 0,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_L_PARENTHESIS,
	TOKEN_R_PARENTHESIS,
	TOKEN_WAVE,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_VAR,
	TOKEN_WORD,
	TOKEN_ARGS,
	TOKEN_DPIPE,
	TOKEN_D_AND,
	TOKEN_WILDCARD,
	TOKEN_FILE,
	TOKEN_CMD,
	TOKEN_LIMITER,
	TOKEN_SPACE
};

typedef struct s_map
{
	char		*symbol;
	int			token;
}	t_tokenmap;

typedef struct __attribute__((packed)) s_token
{
	int				priority;
	int				index;
	char			*content;
	enum e_token	type;
	struct s_token	*next;
}	t_token;

// TOKEN
t_token			*token_init(char *content, int type);
int				token_listsize(t_token *list);
void			token_push(t_token **lst, t_token *token);
void			free_token(t_token *lst);

// TOKENIZER
int				check_simple_token(char *str);
int				check_var_space(char *str);
int				find_token(t_tokenmap *token_map, char *str);
int				scan_token(char *str);
t_token			*parse_string(char *str);
int				check_multiple_pipe_and(char *str);
int				identify_space(char *str);

#endif
