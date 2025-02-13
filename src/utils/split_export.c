/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:12:05 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:23 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_words(char const *s)
{
	size_t	i;
	int		count;
	int		in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '"')
			in_quotes = !in_quotes;
		if (!in_quotes && s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free_all(char **result, int words)
{
	while (words >= 0)
	{
		lp_free(result[words]);
		words--;
	}
	lp_free(result);
}

static void	ft_search_index(char const *s, int *start, int *end)
{
	int	in_quotes;

	while (s[*end] == ' ')
		(*end)++;
	*start = *end;
	in_quotes = 0;
	while (s[*end])
	{
		if (s[*end] == '"')
			in_quotes = !in_quotes;
		if (!in_quotes && s[*end + 1] == ' ')
		{
			(*end)++;
			break ;
		}
		if (!s[*end + 1])
		{
			(*end)++;
			break ;
		}
		(*end)++;
	}
}

static int	ft_write_word(char const *s, char **word, int start_index,
	int end_index)
{
	int	i;

	*word = lp_alloc(sizeof(char) * (end_index - start_index + 1));
	if (!*word)
		return (0);
	i = 0;
	while (start_index < end_index)
	{
		(*word)[i] = s[start_index];
		start_index++;
		i++;
	}
	(*word)[i] = '\0';
	return (1);
}

char	**split_export(char const *str)
{
	char	**result;
	int		words;
	int		i;
	int		start;
	int		end;

	if (!str)
		return (NULL);
	words = ft_count_words(str);
	result = lp_alloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i < words)
	{
		ft_search_index(str, &start, &end);
		if (!ft_write_word(str, &result[i], start, end))
			return (ft_free_all(result, i - 1), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
