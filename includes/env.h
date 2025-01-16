/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:05:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/16 07:16:50 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <minishell.h>


t_list	*env_fill_list(char **envp);
void	env_list_insert(t_list **lst, t_list *node);

#endif
