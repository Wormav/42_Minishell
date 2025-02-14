/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:37:41 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/14 10:09:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_options(t_cmd *cmd, t_env *env, t_data *data)
{
	if (!ft_strcmp(cmd->options[0], "--"))
		return (cd_case_twoo(env));
	if (!ft_strcmp(cmd->options[0], "-"))
		return (cd_case_one(env));
	ft_printf(2, "%s", handle_bad_option(cmd->options[0], "cd"));
	data->error = 2;
	return (1);
}

static void	update_env_after_cd(t_env *env, char *expanded_path, t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env_list_insert(&env, env_lstnew(ft_strsjoin(2, "OLDPWD=", pwd)));
	env_list_insert(&env, env_lstnew(ft_strsjoin(2, "PWD=", expanded_path)));
	free(pwd);
	data->error = 0;
}

static void	handle_cd_execution(t_env *env, t_cmd *cmd, t_data *data)
{
	int		chdir_return;
	char	*expanded_path;

	data->error = 1;
	expanded_path = cd_expand_tilde(cmd->params, env);
	if (access(expanded_path, 0) == F_OK)
	{
		chdir_return = chdir(expanded_path);
		if (chdir_return == 0)
			update_env_after_cd(env, expanded_path, data);
		else
			ft_printf(2, "minishell: cd: %s: No such file or directory\n",
				expanded_path);
	}
	else
		ft_printf(2, "minishell: No such file or directory\n");
	lp_free(expanded_path);
}

void	execute_cd(t_env *env, t_cmd *cmd, t_data *data)
{
	int		options;
	char	**params;

	options = 0;
	if (cmd->options)
		options = check_options(cmd, env, data);
	if (cmd->params[0] != 0)
	{
		params = ft_split(cmd->params, ' ');
		if (params[1])
		{
			data->error = 1;
			ft_printf(2, "minishell: cd: too many arguments\n");
			return ;
		}
	}
	if (cmd->params[0] == 0)
		cmd->params = ft_strdup(env_get_value(env, "$HOME"));
	if (!options)
		handle_cd_execution(env, cmd, data);
}
