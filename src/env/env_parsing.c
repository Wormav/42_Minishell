/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:42:12 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 18:33:30 by jlorette         ###   ########.fr       */
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

t_envp	*env_fill_list(char **envp)
{
	t_envp	*lst;

	lst = NULL;
	if (!*envp || !envp)
		return (NULL);
	while (*envp)
	{
		env_lstadd_back(&lst, env_lstnew(*envp));
		envp++;
	}
	return (lst);
}

void	env_list_insert(t_envp **lst, t_envp *node)
{
	t_envp	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (check_dup(tmp->content, node->content) == 1)
		{
			tmp->content = node->content;
			lp_free(node);
			return ;
		}
		tmp = tmp->next;
	}
	env_lstadd_back(lst, node);
}

void	env_list_remove(t_envp **lst, char *to_remove)
{
	t_envp	*tmp;
	t_envp	*prev;

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
			lp_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	env_list_free(t_envp **lst)
{
	t_envp	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free(tmp);
		tmp = *lst;
	}
	*lst = NULL;
}
