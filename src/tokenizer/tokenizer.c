/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:11:22 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 11:14:02 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

static int	check_end_of_token(char *str)
{
	char	*start;
	int		size;

	start = str;
	size = check_var(str);
	if (!str || !*str)
		return (0);
	if (size)
		return (size);
	size = check_multiple_pipe_and(str);
	if (size)
		return (size);
	if (*start == '\'' || *start == '"')
		return (1);
	if (check_simple_token(start) == 1)
		return (1);
	if (check_simple_token(start) == 2)
		return (2);
	while (*start && !ft_strchr(" |$<>\"'()", *start) && *start != ' ')
		start++;
	return (start - str);
}

static void	fill_node(t_token **head, char *str, char **remain)
{
	int		size;
	char	*parse_str;
	int		token_type;

	size = check_end_of_token(str);
	if (size <= 0)
	{
		*remain = str + 1;
		return ;
	}
	parse_str = ft_substr(str, 0, size);
	if (!parse_str)
	{
		free(parse_str);
		*remain = str + size;
		return ;
	}
	token_type = scan_token(parse_str);
	if (token_type != -1)
		token_push(head, token_init(parse_str, token_type));
	free(parse_str);
	*remain = str + size;
}

t_token	*parse_string(char *str)
{
	t_token	*lst;
	char	*prev;

	lst = NULL;
	while (*str)
	{
		if (*str == ' ')
		{
			str++;
			continue ;
		}
		prev = str;
		fill_node(&lst, str, &str);
		if (str == prev)
			str++;
	}
	return (lst);
}
