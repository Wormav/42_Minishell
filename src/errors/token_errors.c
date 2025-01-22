/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:40:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 17:17:09 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// !code d'erreur a change en fonction de la sortie

void	token_identify_error(int error, t_token *lst, char *str)
{
	lp_free(str);
	free_token(lst);
	if (error == ERR_ODD_QUOTE)
		write (2, "Not an odd number of quote\n", 27);
	else if (error == ERR_ODD_DQUOTE)
		write (2, "Not an odd number of dquote\n", 28);
	exit(1);
}
