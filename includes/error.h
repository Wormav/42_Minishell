/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:23:44 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/11 04:59:50 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <minishell.h>

enum	e_parser_error
{
	PARENTHESIS = 1,
	DOUBLE_AND,
	DOUBLE_PIPE
};

void	check_unsupported_char(t_token *lst, int *flag);
void	token_identify_error(int error, t_token *lst, char *str);
void	parser_identify_error(int error, t_token *lst, char *str);

#endif
