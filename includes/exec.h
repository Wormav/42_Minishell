/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:07:34 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/16 08:09:12 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include <ast.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**options;
	char	*params;
}	t_cmd;

t_cmd *exec_create_cmd(t_ast *ast);

#endif
