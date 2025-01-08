/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:19:29 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/08 09:09:50 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <parser.h>


static int	__join_tokens(t_token *current)
{
	char	*temp_str;
	t_token	*to_free;

	// Fusionne le contenu actuel avec le contenu du token suivant
	temp_str = ft_strjoin(current->content, current->next->content);
	if (!temp_str)
		return (0);

	// Remplace le contenu du token courant par la nouvelle chaîne
	free(current->content);
	current->content = temp_str;

	// Supprime le token suivant après la fusion
	to_free = current->next;
	current->next = to_free->next;
	free(to_free->content);
	free(to_free);

	return (1);
}


t_token	*process_quotes(t_token *start)
{
	t_token	*current;

	current = start->next;
	while (current && current->type != TOKEN_QUOTE)
	{
		if (!__join_tokens(start))
			return (start); // Retourne l'état partiel en cas d'échec
		current = start->next; // Avance après la fusion
	}
	if (current && current->type == TOKEN_QUOTE)
	{
		if (!__join_tokens(start))
			return (start); // Fusion du TOKEN_QUOTE fermant
		return (start->next); // Retourne le token après la fusion complète
	}
	return (start); // Retourne la position si guillemet fermant manquant
}

t_token	*process_dquotes(t_token *start)
{
	t_token	*current;

	current = start->next;
	while (current && current->type != TOKEN_DQUOTE)
	{
		if (!__join_tokens(start))
			return (start); // Retourne l'état partiel en cas d'échec
		current = start->next; // Avance après la fusion
	}
	if (current && current->type == TOKEN_DQUOTE)
	{
		if (!__join_tokens(start))
			return (start); // Fusion du TOKEN_QUOTE fermant
		return (start->next); // Retourne le token après la fusion complète
	}
	return (start); // Retourne la position si guillemet fermant manquant
}

t_token	*parser_quotes(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == TOKEN_QUOTE)
			current = process_quotes(current);
		else
			current = current->next;
	}
	return (list);
}

t_token	*parser_dquotes(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == TOKEN_QUOTE)
			current = process_quotes(current);
		else
			current = current->next;
	}
	return (list);
}

t_token	*parser_quotes_dquotes(t_token *list)
{
	list = parser_quotes(list);
	list = parser_dquotes(list);
	return (list);
}
