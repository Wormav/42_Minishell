/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:40:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/13 18:38:40 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_identify_error(t_data *data, t_token *lst)
{
	if (data->str_prompt)
		lp_free(data->str_prompt);
	if (lst)
		free_token(lst);
	if (data->error_parsing == ERR_ODD_QUOTE)
		write (2, "Not an odd number of quote\n", 27);
	else if (data->error_parsing == ERR_ODD_DQUOTE)
		write (2, "Not an odd number of dquote\n", 28);
}
