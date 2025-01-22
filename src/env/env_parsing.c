/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:42:12 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 18:41:50 by jlorette         ###   ########.fr       */
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

t_env	*env_fill_list(char **envp)
{
	t_env	*lst;

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

void	env_list_insert(t_env **lst, t_env *node)
{
	t_env	*tmp;

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

void	env_list_remove(t_env **lst, char *to_remove)
{
	t_env	*tmp;
	t_env	*prev;

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

void	env_list_free(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free(tmp);
		tmp = *lst;
	}
	*lst = NULL;
}
