/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:37:41 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/30 10:37:18 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	case_twoo(t_env *env)
{
	int		chdir_return;
	char	*tmp;
	char	*home;
	char	*oldpwd;

	home = env_get_value(env, "$HOME");
	oldpwd = env_get_value(env, "$OLDPWD");
	if (home && access(home, 0) == F_OK)
	{
		tmp = env_get_value(env, "$PWD");
		chdir_return = chdir(home);
		if (chdir_return == 0)
		{
			env_list_insert(&env,
				env_lstnew(ft_strsjoin(2, "OLDPWD=", tmp)));
			env_list_insert(&env, env_lstnew(ft_strsjoin(2, "PWD=",
						oldpwd)));
		}
		else
			printf("bash: cd: %s: No such file or directory\n", home);
	}
	else
		printf("bash: cd: HOME not set\n");
	return (1);
}

static int	case_one(t_env *env)
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
			printf("bash: cd: %s: No such file or directory\n", oldpwd);
	}
	else
		printf("bash: cd: OLDPWD not set\n");
	return (1);
}

static int	check_options(t_cmd *cmd, t_env *env, long *error)
{
	if (!ft_strcmp(cmd->options[0], "--"))
		return (case_twoo(env));
	if (!ft_strcmp(cmd->options[0], "-"))
		return (case_one(env));
	printf("%s", handle_bad_option(cmd->options[0], "cd"));
	*error = 2;
	return (1);
}

static void	handle_cd_execution(t_env *env, t_cmd *cmd, long *error)
{
	int	chdir_return;

	if (access(cmd->params, 0) == F_OK)
	{
		chdir_return = chdir(cmd->params);
		if (chdir_return == 0)
		{
			env_list_insert(&env,
				env_lstnew(ft_strsjoin(2, "OLDPDW", execute_pwd(cmd, error))));
			env_list_insert(&env, env_lstnew(ft_strsjoin(2, "PWD=",
						cmd->params)));
		}
		else
			printf("bash: cd: %s: No such file or directory\n", cmd->params);
	}
	else
		printf("Minishell: %s not a directory\n", cmd->params);
}

void	execute_cd(t_env *env, t_cmd *cmd, long *error)
{
	int		options;
	char	**params;

	options = 0;
	if (cmd->options)
		options = check_options(cmd, env, error);
	if (cmd->params[0] != 0)
	{
		params = ft_split(cmd->params, ' ');
		if (params[1])
		{
			*error = 1;
			printf("bash: cd: too many arguments\n");
			return ;
		}
	}
	if (cmd->params[0] == 0)
		cmd->params = ft_strdup(env_get_value(env, "$HOME"));
	if (env_has_env_vars(cmd->params))
		cmd->params = env_replace_env_vars(env, cmd->params);
	if (!options)
		handle_cd_execution(env, cmd, error);
}
