/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:53:28 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:33:30 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    env_lstadd_back(t_envp **lst, t_envp *new)
{
        t_envp  *tmp;

        if (!lst || !new)
                return ;
        tmp = *lst;
        if (!*lst)
        {
                *lst = new;
                return ;
        }
        while (tmp->next)
                tmp = tmp->next;
        tmp->next = new;
}

t_envp  *env_lstnew(void *content)
{
        t_envp  *node;

        node = lp_alloc(sizeof(t_envp));
        if (node)
        {
                node->content = content;
                node->next = NULL;
        }
        return (node);
}
