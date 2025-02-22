/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:12:22 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/21 15:37:51 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_state(t_space_state *state, char *str)
{
	state->result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	state->i = 0;
	state->j = 0;
	state->in_quotes = 0;
	state->quote_type = 0;
}

char	*reduce_spaces(char *str)
{
	t_space_state	state;

	init_state(&state, str);
	while (str[state.i])
	{
		if ((str[state.i] == '"' || str[state.i] == '\'')
			&& (!state.in_quotes || state.quote_type == str[state.i]))
		{
			state.quote_type = str[state.i];
			state.in_quotes = !state.in_quotes;
			state.result[state.j++] = str[state.i];
		}
		else if (state.in_quotes)
			state.result[state.j++] = str[state.i];
		else if (str[state.i] == ' ')
		{
			if (state.i == 0 || str[state.i - 1] != ' ')
				state.result[state.j++] = ' ';
		}
		else
			state.result[state.j++] = str[state.i];
		state.i++;
	}
	state.result[state.j] = '\0';
	return (state.result);
}
