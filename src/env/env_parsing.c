/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:42:12 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/16 09:49:54 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <math.h>

static int	check_dup(t_list *node1, t_list *node2)
{
	int	i;
	char	*content1;
	char	*content2;

	i = 0;
	content1 = (char *)node1->content;
	content2 = (char *)node2->content;
	while (content1[i] && content1[i] != '=')
		i++;
	return (!ft_strncmp(content1, content2, i + 1));
}

t_list *env_fill_list(char **envp)
{
    t_list *lst = NULL;
	
	if (!*envp || !envp)
		return (NULL);
    while (*envp)
    {
        ft_lstadd_back(&lst, ft_lstnew(*envp));
        envp++;
    }
    return (lst);
}

void env_list_insert(t_list **lst, t_list *node)
{
    t_list *tmp = *lst;

	while (tmp)
	{
		if (check_dup(tmp, node) == 1)
		{
			tmp->content = ft_strdup(node->content);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(lst, node);
}

