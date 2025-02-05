/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:35:46 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/05 16:39:53 by swenntetrel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print_error_syntax(int err)
{
	if (err == ERR_SYNTAX_PIPE)
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
	else 
		return (0);
	return (1);
}

static t_token	*skip_space_token(t_token *lst)
{
	while (lst && lst->type != TOKEN_SPACE)
		lst = lst->next;
	return (lst);
}

static int	check_syntax(t_token *prev, t_token *current)
{
	if (!prev && current->type == TOKEN_PIPE)
		return (ERR_SYNTAX_PIPE);
	if (prev && prev->type == TOKEN_PIPE)
	{
		current = skip_space_token(current);
		if (!current || current->type != TOKEN_CMD)
			return (ERR_SYNTAX_PIPE);
	}
	return(0);
}

void	parser_errors_syntax(t_token *lst, int *error)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		if (!prev && print_error_syntax(check_syntax(prev, tmp)))
		{
			*error = 2;
			break ;
		}
		if (prev && print_error_syntax(check_syntax(prev, tmp)))
		{
			*error = 2;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
