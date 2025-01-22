/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:45:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 07:46:40 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *env_get_value(t_list *env, char *key)
{
    t_list *tmp;
    int keylen;

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
