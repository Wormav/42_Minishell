/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:53:37 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/14 10:08:23 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cd_expand_tilde(char *path, t_env *env)
{
	char	*home;

	if (path && path[0] == '~')
	{
		home = env_get_value(env, "$HOME");
		if (!home)
			return (ft_strdup(path));
		if (path[1] == '\0')
			return (ft_strdup(home));
		if (path[1] == '/')
			return (ft_strsjoin(2, home, path + 1));
	}
	return (ft_strdup(path));
}

int	cd_case_twoo(t_env *env)
{
	int		chdir_return;
	char	*tmp;
	char	*home;
	char	*oldpwd;

	home = env_get_value(env, "$HOME");
	oldpwd = env_get_value(env, "$OLDPWD");
	if (!home || !oldpwd)
		return (1);
	if (home && access(home, 0) == F_OK)
	{
		tmp = env_get_value(env, "$PWD");
		chdir_return = chdir(home);
		if (chdir_return == 0)
		{
			env_list_insert(&env, env_lstnew(ft_strsjoin(2, "OLDPWD=", tmp)));
			env_list_insert(&env, env_lstnew(ft_strsjoin(2, "PWD=", oldpwd)));
		}
		else
			ft_printf(2, "minishell: cd: %s: No such file or directory\n",
				home);
	}
	else
		ft_printf(2, "minishell: cd: HOME not set\n");
	return (1);
}

int	cd_case_one(t_env *env)
{
	int		chdir_return;
	char	*tmp;
	char	*oldpwd;

	oldpwd = env_get_value(env, "$OLDPWD");
	if (oldpwd && access(oldpwd, 0) == F_OK)
	{
		tmp = env_get_value(env, "$PWD");
		chdir_return = chdir(oldpwd);
		if (chdir_return == 0)
		{
			env_list_insert(&env,
				env_lstnew(ft_strsjoin(2, "OLDPWD=", tmp)));
			env_list_insert(&env, env_lstnew(ft_strsjoin(2, "PWD=",
						oldpwd)));
		}
		else
			ft_printf(2, "minishell: cd: %s: No such file or directory\n",
				oldpwd);
	}
	else
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
	return (1);
}
