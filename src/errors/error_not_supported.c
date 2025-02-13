/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_not_supported.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 15:37:09 by jlorette         ###   ########.fr       */
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
		else if (lst->type == TOKEN_WILDCARD)
			break ;
		else if (lst->type == TOKEN_SEMICOLON)
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
		ft_printf(2, "We don't support subshell...\n");
	else if (err == TOKEN_D_AND)
		ft_printf(2, "We don't support &&...\n");
	else if (err == TOKEN_DPIPE)
		ft_printf(2, "We don't support ||...\n");
	else if (err == TOKEN_WILDCARD)
		ft_printf(2, "We don't support *...\n");
	else if (err == TOKEN_SEMICOLON)
		ft_printf(2, "We don't support ;...\n");
	return ;
}
