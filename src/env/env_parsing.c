/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:42:12 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/21 14:33:52 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_dup(char *node1, char *node2)
{
	int	i;

	i = 0;
	while (node1[i] && node1[i] != '=')
		i++;
	return (!ft_strncmp(node1, node2, i));
}

t_list	*env_fill_list(char **envp)
{
	static t_list	*lst;

	lst = NULL;
	if (!*envp || !envp)
		return (NULL);
	while (*envp)
	{
		ft_lstadd_back(&lst, ft_lstnew(*envp));
		envp++;
	}
	return (lst);
}

void	env_list_insert(t_list **lst, t_list *node)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (check_dup(tmp->content, node->content) == 1)
		{
			tmp->content = ft_strdup(node->content);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(lst, node);
}

void	env_list_remove(t_list **lst, char *to_remove)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		if (check_dup(tmp->content, to_remove) == 1)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	env_list_free(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free(tmp);
		tmp = *lst;
	}
	*lst = NULL;
}
