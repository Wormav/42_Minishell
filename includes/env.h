/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:05:43 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/22 08:05:25 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <minishell.h>

t_list	*env_fill_list(char **envp);
void	env_list_insert(t_list **lst, t_list *node);
void	env_list_remove(t_list **lst, char *to_remove);
void	env_list_free(t_list **lst);
void	env_print(t_list *lst);
char    *env_get_value(t_list *env, char *key);
void	env_join(char *to_join, t_list **env);
char	*env_get_value(t_list *env, char *key);

#endif
