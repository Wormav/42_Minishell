/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:35:36 by swenntetrel       #+#    #+#             */
/*   Updated: 2025/01/11 13:07:11 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean(t_ast *ast, t_token *token, char *str)
{
	ast_free(ast);
	free_token(token);
	free(str);
	exit(1);//code erreur a modifier en fonction de la sortie
}
