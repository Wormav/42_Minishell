/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:42:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/09 19:48:45 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

int	check_multiple_pipe_and(char *str)
{
	char	*start;

	start = str;
	while (*start && (*start == '|' || *start == '&' || *start == '*'))
		start++;
	if (start - str >= 3)
		return (start - str);
	return (0);
}

int	check_simple_token(char *str)
{
	static const char	*simple_tokens = "|<>()'\"~*";

	if (!str || !*str)
		return (0);
	if (check_multiple_pipe_and(str))
		return (check_multiple_pipe_and(str));
	if (ft_strchr(simple_tokens, *str))
	{
		if (*(str + 1) && ft_strchr("|<>&", *(str + 1)))
			return (2);
		return (1);
	}
	return (0);
}

int	check_var_space(char *str)
{
	char	*start;

	start = str;
	if (*start == ' ')
	{
		while (start && *start == ' ')
			start++;
		return (start - str);
	}
	if (*str == '$')
		while (*str && !ft_strchr(" |<>~()", *str))
			str++;
	return (str - start);
}

int	find_token(t_tokenmap *token_map, char *str)
{
	int	i;

	i = 0;
	if (identify_space(str))
		return (TOKEN_SPACE);
	if (check_multiple_pipe_and(str))
		return (TOKEN_WORD);
	if (!ft_strcmp(str, "||"))
		return (TOKEN_DPIPE);
	if (!ft_strcmp(str, "&&"))
		return (TOKEN_D_AND);
	if (*str == '$')
		return (TOKEN_VAR);
	if (*str == '-')
		return (TOKEN_ARGS);
	while (token_map[i].symbol != NULL)
	{
		if (!ft_strcmp(str, token_map[i].symbol))
			return (token_map[i].token);
		i++;
	}
	return (TOKEN_WORD);
}

int	scan_token(char *str)
{
	static t_tokenmap	static_map[] = {{"|", TOKEN_PIPE}, {"<",
		TOKEN_REDIR_IN}, {">", TOKEN_REDIR_OUT}, {"\"", TOKEN_DQUOTE}, {"'",
		TOKEN_QUOTE}, {"<<", TOKEN_HEREDOC}, {">>", TOKEN_APPEND}, {"(",
		TOKEN_L_PARENTHESIS}, {")", TOKEN_R_PARENTHESIS}, {"~", TOKEN_WAVE},
	{"-", TOKEN_ARGS}, {"||", TOKEN_DPIPE}, {"*", TOKEN_WILDCARD},
	{NULL, TOKEN_WORD}};

	return (find_token(static_map, str));
}
