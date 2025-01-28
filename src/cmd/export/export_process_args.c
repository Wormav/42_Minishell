/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_process_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:46:00 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/28 11:56:16 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_args_with_value(char **split_equal, int valid_key,
t_env **env)
{
	char	*tmp;
	char	*env_value;

	tmp = NULL;
	if (valid_key == 1)
	{
		tmp = ft_strsjoin(6, "declare -x ", split_equal[0], "=",
				"\"", split_equal[1], "\"");
	}
	else if (valid_key == 2)
	{
		env_value = env_get_value(*env, ft_strjoin("$",
					export_remove_plus_before_equal(split_equal[0])));
		if (!env_value)
			env_value = "";
		tmp = ft_strsjoin(7, "declare -x ",
				export_remove_plus_before_equal(split_equal[0]), "=",
				"\"", env_value, split_equal[1], "\"");
	}
	env_list_insert(env, env_lstnew(tmp));
}

void	export_process_args_with_equal(char *split, int valid_key, t_env **env)
{
	char	*tmp;
	char	**split_equal;

	tmp = NULL;
	split_equal = ft_split(split, '=');
	if (split_equal[1])
		process_args_with_value(split_equal, valid_key, env);
	else if (split_equal[0])
	{
		tmp = ft_strsjoin(5, "declare -x ", split_equal[0], "=",
				"\"", "\"");
		env_list_insert(env, env_lstnew(tmp));
	}
	free_split(split_equal);
}

void	export_process_args(char *split, int *error, t_env **env)
{
	int	valid_key;

	valid_key = export_is_valid_key(split);
	if (!valid_key)
	{
		*error = 1;
		printf("bash: export: %s: not a valid identifier\n", split);
		return ;
	}
	if (export_find_next_sign('=', split) != (int)ft_strlen(split))
	{
		export_process_args_with_equal(split, valid_key, env);
	}
	else if (split)
	{
		env_list_insert(env, env_lstnew(split));
	}
}
