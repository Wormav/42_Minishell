/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:44:32 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/17 16:31:18 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_quotes(char *result, int i, int *quote)
{
	if (result[i] == '"' && (i == 0 || result[i - 1] != '\\'))
	{
		if (*quote == 2)
			*quote = 0;
		else if (*quote == 0)
			*quote = 2;
	}
	else if (result[i] == '\'' && (i == 0 || result[i - 1] != '\\'))
	{
		if (*quote == 1)
			*quote = 0;
		else if (*quote == 0)
			*quote = 1;
	}
	else if (result[i] == '\t' && *quote == 0)
		result[i] = ' ';
	return (i + 1);
}

char	*filter_tab(char *str)
{
	int		i;
	int		quote;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	quote = 0;
	while (result[i])
		i = handle_quotes(result, i, &quote);
	return (result);
}
