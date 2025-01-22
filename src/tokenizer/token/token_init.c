/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:43:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 17:12:11 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*token_init(char *content, int type, int priority)
{
	t_token	*token;

	token = lp_alloc(sizeof(t_token));
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	token->priority = priority;
	token->index = 0;
	return (token);
}
