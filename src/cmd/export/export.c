/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:20:58 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/28 11:35:59 by jlorette         ###   ########.fr       */
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

int has_equal_sign(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int check_params(char *str)
{
	if (!str)
		return (0);
	while (*str && *str == ' ')
		str++;
	if (*str == '=')
		return (0);
	while (*str && *str != '=' && *str != ' ')
		str++;
	if (*str == ' ')
	{
		while (*str && *str == ' ')
			str++;
		if (*str == '=')
			return (0);
	}
	if (*str == '=')
	{
		str++;
		while (*str && *str == ' ')
			str++;
		if (!*str)
			return (1);
		while (*str && *str != ' ')
			str++;
		if (*str)
			return (2);
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

char *remove_plus_before_equal(char *str)
{
	char *ret;
	int i;
	int j;

	ret = lp_alloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '\0')
			i++;
		ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}

void process_args_with_equal(char *split, int valid_key, t_env **env)
{
	char *tmp = NULL;
	char **split_equal;
	char *env_value;

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
			env_value = env_get_value(*env, ft_strjoin("$",
					remove_plus_before_equal(split_equal[0])));
			if (!env_value)
				env_value = "";
			tmp = ft_strsjoin(7, "declare -x ",
					remove_plus_before_equal(split_equal[0]), "=",
							  "\"", env_value, split_equal[1], "\"");
		}
	}
	else if(split_equal[0])
	{
		tmp = ft_strsjoin(5, "declare -x ", split_equal[0], "=",
				"\"", "\"");
	}
	free_split(split_equal);
	env_list_insert(env, env_lstnew(tmp));
}

void process_args(char *split, int *error, t_env **env)
{
	int valid_key;

	valid_key = is_valid_key(split);
	if (!valid_key)
	{
		*error = 1;
		printf("bash: export: %s: not a valid identifier\n", split);
		return;
	}
	if (find_next_sign('=', split) != (int)ft_strlen(split))
	{
		process_args_with_equal(split, valid_key, env);
	}
	else if (split)
	{
		env_list_insert(env, env_lstnew(split));
	}
}

void	process_params(t_env *env, t_cmd *cmd, int *error)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(env_replace_env_vars(env, cmd->params), ' ');
	while (split[i])
	{
		if (split[i][0] == '=')
		{
			*error = 1;
			printf("bash: export: ʻ%s’: not a valid identifier\n", split[i]);
			free_split(split);
			return ;
		}
		i++;
	}
	i = 0;
	while (split[i])
	{
		if (!has_equal_sign(split[i]))
		{
			free_split(split);
			return;
		}
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
