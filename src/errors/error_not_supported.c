/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_not_supported.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 11:14:04 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_unsupported_char(t_token *lst, int *err)
{
	while (lst)
	{
		if (lst->type == TOKEN_L_PARENTHESIS
			|| lst->type == TOKEN_R_PARENTHESIS)
			break ;
		else if (lst->type == TOKEN_D_AND)
			break ;
		else if (lst->type == TOKEN_DPIPE)
			break ;
		lst = lst->next;
	}
	if (lst)
		*err = lst->type;
}

void	parser_identify_error(int err, t_token *lst, char *str)
{
	lp_free(str);
	free_token(lst);
	if (err == TOKEN_L_PARENTHESIS || err == TOKEN_R_PARENTHESIS)
		write (2, "We don't support subshell...\n\n", 25);
	else if (err == TOKEN_D_AND)
		write (2, "We don't support &&...\n\n", 22);
	else if (err == TOKEN_DPIPE)
		write (2, "We don't support ||...\n\n", 21);
	return ;
}
