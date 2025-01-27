/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/27 14:43:01 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_valid_key(char *str)
{
	if (ft_isdigit(*str) || *str == '=')
	 	return (0);
	while (str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
		{
			if ((*str == '+') && (*(str + 1) == '='))
				return (2);
			return (0);
		}
		str++;
	}
	return (1);
}

int	find_next_sign(char sign, char *str)
{
	char	*start;

	start = str;
	str++;
	while (*str && *str != sign)
		str++;
	return (str - start);
}

void	process_args(char *split, int *error, t_env **env)
{
	char	*tmp = NULL;
	char	**split_equal;
	int valid_key;
	char *env_value;

	valid_key = is_valid_key(split);

	if (!valid_key)
	{
		*error = 1;
		printf("bash: export: %s: not a valid identifier\n", split);
		return ;
	}
	if (find_next_sign('=', split) != (int)ft_strlen(split))
	{
		split_equal = ft_split(split, '=');
		if (split_equal[1])
		{
			if (valid_key == 1)
			{
				tmp = ft_strsjoin(6, "declare -x ", split_equal[0], "=",
					"\"", split_equal[1], "\"");
			}
			else if (valid_key == 2)
			{
				env_value = env_get_value(*env, ft_strjoin("$",split_equal[0]));
				printf("ICI =======================> %s\n", env_value);
				if (!env_value)
					env_value = "";
				tmp = ft_strsjoin(7, "declare -x ", split_equal[0], "=",
								  "\"", env_value, split_equal[1], "\"");
			}
		}
		free_split(split_equal);
		env_list_insert(env, env_lstnew(tmp));
	}
	else if (split)
		env_list_insert(env, env_lstnew(split));
}

void	process_params(t_env *env, t_cmd *cmd, int *error)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(env_replace_env_vars(env, cmd->params), ' ');
	while (split[i])
	{
		process_args(split[i], error, &env);
		if (*error)
		{
			free_split(split);
			return ;
		}
		i++;
	}
}

void	ft_export(t_env **env, t_cmd *cmd, int *error)
{
	if (cmd->options)
	{
		*error = 1;
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
