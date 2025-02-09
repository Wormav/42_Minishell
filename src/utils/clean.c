/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:35:36 by swenntetrel       #+#    #+#             */
/*   Updated: 2025/02/09 18:30:57 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean_memory(t_ast *ast, t_token *token, char *str)
{
    if (ast)
        ast_free(ast);
    if (token)
        free_token(token);
    if (str && str != NULL)
        lp_free(str);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		lp_free(split[i]);
		i++;
	}
	lp_free(split);
}
