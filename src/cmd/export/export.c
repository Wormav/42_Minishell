/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/02/04 07:54:11 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	validate_params(char **split, long *error)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '=' || split[i][0] == '-')
		{
			*error = 1;
			printf("minishell: export: `%s': not a valid identifier\n",
				split[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	process_params(t_env *env, t_cmd *cmd, long *error)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(env_replace_env_vars(env, cmd->params), ' ');
	if (!validate_params(split, error))
		return ;
	while (split[i])
	{
		if (!has_equal_sign(split[i]))
		{
			free_split(split);
			return ;
		}
		export_process_args(split[i], error, &env);
		if (*error)
		{
			free_split(split);
			return ;
		}
		i++;
	}
	free_split(split);
}

void	execute_export(t_env **env, t_cmd *cmd, long *error)
{
	if (cmd->options)
	{
		*error = 2;
		printf("%s", handle_bad_option(cmd->options[0], "export"));
		return ;
	}
	if (!*(cmd->params) && !cmd->options)
	{
		env_print(*env);
		return ;
	}
	process_params(*env, cmd, error);
}
