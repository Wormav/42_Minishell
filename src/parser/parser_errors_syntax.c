/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:46 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/13 16:36:54 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print_error_syntax(int err, char *token)
{
	if (!err)
		return (0);
	if (err & ERR_SYNTAX_PIPE)
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n",
			token);
	if (err & ERR_SYNTAX_REDIR)
		ft_printf(
			2, "minishell: syntax error near unexpected token `newline'\n");
	return (1);
}

static t_token	*skip_space_token(t_token *lst)
{
	while (lst && lst->type == TOKEN_SPACE)
		lst = lst->next;
	return (lst);
}

static int	check_syntax_cmd(t_token *token)
{
	char	*tmp;

	tmp = token->content;
	if (*tmp == '\'' || *tmp == '"')
		return (0);
	while (*tmp)
	{
		if (*tmp == '<' || *tmp == '>')
			return (1);
		tmp++;
	}
	return (0);
}

static int	check_syntax(t_token *prev, t_token *current)
{
	if (current->type == TOKEN_WORD && check_syntax_cmd(current))
		return (ERR_SYNTAX_REDIR);
	if (current->type == TOKEN_HEREDOC && (!skip_space_token(current->next)
			|| skip_space_token(current->next)->type != TOKEN_WORD))
		return (ERR_SYNTAX_REDIR);
	if (!prev && current->type == TOKEN_PIPE)
		return (ERR_SYNTAX_PIPE);
	if (!prev && (current->type == TOKEN_APPEND))
		return (ERR_SYNTAX_REDIR);
	if ((current->type == TOKEN_REDIR_IN
			|| current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_APPEND)
		&& skip_space_token(current->next) == NULL)
		return (ERR_SYNTAX_REDIR);
	if (current->type == TOKEN_PIPE && skip_space_token(current->next) == NULL)
		return (ERR_SYNTAX_PIPE);
	if (current->type == TOKEN_PIPE
		&& (skip_space_token(current->next)->type != TOKEN_WORD
			&& skip_space_token(current->next)->type != TOKEN_HEREDOC))
		return (ERR_SYNTAX_PIPE);
	return (0);
}

void	parser_errors_syntax(t_token *lst, long *error, int *err)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		if (!prev && print_error_syntax(check_syntax(prev, tmp), tmp->content))
		{
			*err = 2;
			break ;
		}
		if (prev && print_error_syntax(check_syntax(prev, tmp), tmp->content))
		{
			*err = 2;
			break ;
		}
		prev = tmp;
		tmp = skip_space_token(tmp->next);
	}
	if (*err)
		*error = *err;
}
