/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:17:03 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/25 19:47:15 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_space(char *str)
{
	char	*start;

	start = str;
	while (*str && *str == ' ')
		str++;
	return (str - start);
}

int	find_first_size(char *str)
{
	char	*start;
	int		flag;

	start = str;
	flag = 1;
	if (*str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
	}
	else if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
	}
	else
	{
		flag = 0;
		while (*str && *str != ' ')
			str++;
	}
	return ((str - start) + flag);
}

int	find_next_size(char *str)
{
	char	*start;

	start = str;
	while (*str && *str != ' ')
	{
		if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
			return (str - start + 1);
		}
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			return (str - start + 1);
		}
		str++;
	}
	return (str - start);
}

int	check_opts(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (!ft_strncmp(str, "'-", 2) || !ft_strncmp(str, "\"-", 2))
		str++;
	return (*str == '-');
}

int	count_args(char *str)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*str)
	{
		str += skip_space(str);
		if (!*str)
			break ;
		if (*str == '\'' || *str == '"')
			in_quotes = 1;
		if (*str == '-' || in_quotes)
		{
			count++;
			str += find_next_size(str);
			in_quotes = 0;
			continue ;
		}
		break ;
	}
	return (count);
}
