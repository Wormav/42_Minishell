/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_only_dquotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:17:57 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 08:18:47 by jlorette         ###   ########.fr       */
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

static void	process_dquotes(const char *str, char *new, int *i, int *j)
{
	int		in_quotes;
	char	quote_type;

	in_quotes = 0;
	quote_type = 0;
	while (str[*i])
	{
		if (str[*i] == '"' && (!in_quotes || quote_type == '"'))
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

static char	*remove_dquotes(const char *str)
{
	char	*new;
	int		i;
	int		j;

	if (!init_quote_removal(str, &new, &i, &j))
		return (NULL);
	process_dquotes(str, new, &i, &j);
	return (new);
}

char	*parser_filter_dquote(char *str)
{
	char	*cleaned_params;

	if (!str)
		return (NULL);
	cleaned_params = remove_dquotes(str);
	if (cleaned_params)
		str = cleaned_params;
	return (str);
}
