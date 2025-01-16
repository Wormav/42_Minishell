/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:00:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/16 14:01:03 by stetrel          ###   ########.fr       */
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
	int		count;
	char	*prev;

	count = 0;
	prev = str;
	while (*str)
	{
		str += skip_space(str);
		if (ft_strncmp(str, "-", 1))
			break ;
		if ((*str == '\'' || *str == '"' || *str == '-') && *(str - 1) == ' ')
		{
			prev = str;
			count++;
			str += find_next_size(str);
		}
		if (prev == str)
			str++;
	}
	return (count);
}
