/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:30:57 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/24 16:05:30 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	struct s_env	*next;
	void		*content;
}	t_env;


t_env	*env_fill_list(char **envp);
void	env_list_insert(t_env **lst, t_env *node);
void	env_list_remove(t_env **lst, char *to_remove);
void	env_list_free(t_env **lst);
void	env_print(t_env *lst);
char    *env_get_value(t_env *env, char *key);
void	env_join(char *to_join, t_env **env);
char	*env_get_value(t_env *env, char *key);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lstnew(void *content);

#endif
