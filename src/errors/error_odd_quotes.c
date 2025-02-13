/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_odd_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:55:03 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 18:35:26 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_odd_quotes(char *str, int *err)
{
    int	quotes;
    int	dquotes;
    int	i;

    quotes = 0;
    dquotes = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '"' && !quotes)
            dquotes = !dquotes;
        else if (str[i] == '\'' && !dquotes)
            quotes = !quotes;
        i++;
    }
    if (quotes)
        *err = ERR_ODD_QUOTE;
    else if (dquotes)
        *err = ERR_ODD_DQUOTE;
}
