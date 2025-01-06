/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:43:13 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 09:54:22 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

t_token	*token_init(char *content, t_tokens type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	return (token);
}
