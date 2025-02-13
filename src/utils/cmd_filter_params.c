/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filter_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:51:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 10:03:15 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_filter_params(t_cmd **cmd)
{
	if (!ft_strcmp((*cmd)->cmd, "pwd"))
		(*cmd)->params = parser_filter_quote((*cmd)->params);
	else if (!ft_strcmp((*cmd)->cmd, "unset"))
		(*cmd)->params = parser_filter_quote((*cmd)->params);
	else if (!ft_strcmp((*cmd)->cmd, "cd"))
		(*cmd)->params = parser_filter_quote((*cmd)->params);
	else if (!ft_strcmp((*cmd)->cmd, "exit"))
		(*cmd)->params = parser_filter_quote((*cmd)->params);
	else if (!ft_strcmp((*cmd)->cmd, "env"))
		(*cmd)->params = parser_filter_quote((*cmd)->params);
}
