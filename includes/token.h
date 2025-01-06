/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:49:56 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 10:03:32 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/include/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum __attribute__((packed)) e_token
{
	TOKEN_PIPE = 1 << 0,
	TOKEN_QUOTE = 1 << 1,
	TOKEN_DQUOTE = 1 << 2,
	TOKEN_REDIR_IN = 1 << 3,
	TOKEN_REDIR_OUT = 1 << 4,
	TOKEN_L_PARENTHESIS = 1 << 5,
	TOKEN_R_PARENTHESIS = 1 << 6,
	TOKEN_WAVE = 1 << 7,
	TOKEN_HEREDOC = 1 << 8,
	TOKEN_APPEND = 1 << 9,
	TOKEN_VAR = 1 << 10,
	TOKEN_WORD = 1 << 11,
	TOKEN_ARGS = 1 << 12,
}				t_tokens;

typedef struct s_map
{
	char		*symbol;
	int			token;
}				t_tokenmap;

typedef struct __attribute__((packed)) s_token
{
	const char		*content;
	t_tokens		type;
	struct s_token	*next;
}	t_token;

// TOKEN
t_token			*token_init(char *content, t_tokens type);
int				token_listsize(t_token *list);
void			token_push(t_token **lst, t_token *token);
void			free_token(t_token *lst);

// TOKENIZER
int				check_simple_token(char *str);
int				check_var(char *str);
int				find_token(t_tokenmap *token_map, char *str);
int				scan_token(char *str);
t_token			*parse_string(char *str);

#endif
