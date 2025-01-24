/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:54:43 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/24 17:08:21 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_get_value(t_env *env, char *key)
{
	t_env	*tmp;
	int		keylen;

	if (!key || !env || key[0] != '$')
		return (NULL);
	key++;
	keylen = ft_strlen(key);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, key, keylen)
			&& ((char *)tmp->content)[keylen] == '=')
			return (((char *)tmp->content) + keylen + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
