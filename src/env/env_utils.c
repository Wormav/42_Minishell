/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:02:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/24 17:09:54 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	env_list_size(t_env *env)
{
	size_t	size;

	if (!env)
		return (0);
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_tab(t_env *env)
{
	char	**envp;
	size_t	i;

	i = 0;
	envp = lp_alloc(sizeof(char *) * env_list_size(env));
	while (i < env_list_size(env))
	{
		envp[i] = lp_alloc(ft_strlen(env->content) + 1);
		ft_memcpy(envp[i], env->content, ft_strlen(env->content));
		i++;
		env = env->next;
	}
	return (envp);
}
