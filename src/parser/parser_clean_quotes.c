/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:18:56 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/28 14:21:52 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*init_quote_removal(const char *str, char **new, int *i, int *j)
{
	if (!str)
		return (NULL);
	*new = lp_alloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!*new)
		return (NULL);
	*i = 0;
	*j = 0;
	return (*new);
}

static void	process_quotes(const char *str, char *new, int *i, int *j)
{
	int		in_quotes;
	char	quote_type;

	in_quotes = 0;
	quote_type = 0;
	while (str[*i])
	{
		if ((str[*i] == '\'' || str[*i] == '"')
			&& (!in_quotes || quote_type == str[*i]))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_type = str[*i];
			else
				quote_type = 0;
			(*i)++;
			continue ;
		}
		new[(*j)++] = str[(*i)++];
	}
	new[*j] = '\0';
}

static char	*remove_quotes(const char *str)
{
	char	*new;
	int		i;
	int		j;

	if (!init_quote_removal(str, &new, &i, &j))
		return (NULL);
	process_quotes(str, new, &i, &j);
	return (new);
}

char	*parser_filter_quote(char *str)
{
	char	*cleaned_params;

	if (!str)
		return (NULL);
	cleaned_params = remove_quotes(str);
	if (cleaned_params)
		str = cleaned_params;
	return (str);
}
