/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:37:29 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 16:39:37 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>

enum	e_error
{
	ERR_ODD_QUOTE = 1,
	ERR_ODD_DQUOTE,
	ERR_ODD_PARENTHESIS
}	e_error;

typedef struct	s_parser
{
	int				type;
	char			*content;
	struct s_parser *next;
}	t_parser;


#endif
