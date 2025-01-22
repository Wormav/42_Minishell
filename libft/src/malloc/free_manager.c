/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:01:33 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/20 10:05:51 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	**alloc_collector(void)
{
	static t_list	*lst;

	return (&lst);
}

__attribute__((destructor))
static void	free_alloc_collector(void)
{
	t_list	**lst;
	t_list	*tmp;

	lst = alloc_collector();
	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

void	lp_free(void *address)
{
	t_list	**lst;
	t_list	*current;
	t_list	*prev;

	if (!address)
		return ;
	lst = alloc_collector();
	current = *lst;
	prev = NULL;
	while (current->content != address)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (prev == NULL)
		*lst = current->next;
	else
		prev->next = current->next;
	free(current->content);
	free(current);
}

static void	lp_push(void *malloc_address)
{
	t_list	**lst;

	lst = alloc_collector();
	ft_lstadd_front(lst, ft_lstnew(malloc_address));
}

void	*lp_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(1, size);
	lp_push(ptr);
	return (ptr);
}
