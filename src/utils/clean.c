/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swenntetrel <swenntetrel@42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:35:36 by swenntetrel       #+#    #+#             */
/*   Updated: 2025/01/11 05:47:54 by swenntetrel      ###   ########.fr       */
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
