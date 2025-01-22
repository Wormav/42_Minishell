/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:30:57 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/22 18:38:22 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <minishell.h>

typedef struct	s_envp
{
	struct s_envp	*next;
	void		*content;
}	t_envp;

t_envp	*env_fill_list(char **envp);
void	env_list_insert(t_envp **lst, t_envp *node);
void	env_list_remove(t_envp **lst, char *to_remove);
void	env_list_free(t_envp **lst);
void	env_print(t_envp *lst);
char    *env_get_value(t_envp *env, char *key);
void	env_join(char *to_join, t_envp **env);
char	*env_get_value(t_envp *env, char *key);
void	env_lstadd_back(t_envp **lst, t_envp *new);
t_envp	*env_lstnew(void *content);

#endif
