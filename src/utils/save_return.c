/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:39:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 19:42:26 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	save_return_val(long *error, t_env **env_lst)
{
	char	*save_return;

	save_return = ft_strsjoin(3, "?=\"", ft_ltoa(*error), "\"");
	env_list_insert(env_lst, env_lstnew(save_return));
}
