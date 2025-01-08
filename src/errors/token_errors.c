/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:40:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/08 10:58:20 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <parser.h>

void	token_identify_error(int error)
{
	if (error == ERR_ODD_QUOTE)
		write (2, "Not an odd number of quote\n", 27);
	else if (error == ERR_ODD_DQUOTE)
		write (2, "Not an odd number of dquote\n", 28);
	else if (error == ERR_ODD_PARENTHESIS)
		write (2, "Not an odd number of parenthesis\n", 33);
}
