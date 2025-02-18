/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:41:18 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/18 12:29:27 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env_print(t_env *lst)
{
	while (lst)
	{
		if (ft_strncmp(lst->content, "?=", 2)
			&& ft_strncmp(lst->content, "PATH=:./", 8))
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
