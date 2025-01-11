/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:11:22 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/11 10:09:04 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

int	identify_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (!(*str));
}

static int	handle_quotes(char *str)
{
	char	*start;
	char	quote;

	start = str;
	if (*start == '\'' || *start == '"')
	{
		quote = *start;
		start++;
		while (*start && *start != quote)
			start++;
		if (*start == quote)
			start++;
		return (start - str);
	}
	return (0);
}

static int	check_end_of_token(char *str)
{
	char	*start;
	int		size;

	if (!*str)
		return (0);
	start = str;
	size = check_var_space(str);
	if (!str || !*str)
		return (0);
	if (size)
		return (size);
	size = check_multiple_pipe_and(str);
	if (size)
		return (size);
	size = handle_quotes(start);
	if (size)
		return (size);
	if (check_simple_token(start) > 0)
		return (check_simple_token(start));
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
		token_push(head, token_init(parse_str, token_type, 0));
	free(parse_str);
	*remain = str + size;
}

t_token	*token_parse_string(char *str)
{
	t_token	*lst;
	char	*prev;

	lst = NULL;
	while (*str)
	{
		prev = str;
		fill_node(&lst, str, &str);
		if (str == prev)
			str++;
	}
	return (lst);
}
