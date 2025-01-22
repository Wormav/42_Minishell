/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:55:05 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 18:41:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"
#include <minishell.h>

void	env_join(char *to_join, t_env **env)
{
	char	*str;
	char	**split;
	char	*join;

	split = ft_split(to_join, '=');
	str = env_get_value(*env, split[0]);
	if (!str)
		return ;
	join = ft_strsjoin(6, split[0], "=", "\"", str, split[1] + 1, "\"");
	lp_free(str);
	env_list_insert(env, env_lstnew(join));
	free_split(split);
}
