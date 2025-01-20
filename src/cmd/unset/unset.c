/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:46 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/20 14:29:24 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*handle_bad_option(char *option)
{
	char	*error_message;
	char	*invalid_option;

	invalid_option = ft_substr(option, 0, 2);
	if (!invalid_option)
		return (NULL);
	error_message = malloc(ft_strlen("bash: unset: ") + ft_strlen(invalid_option)
			+ ft_strlen(": invalid option\n") + 1);
	if (!error_message)
	{
		free(invalid_option);
		return (NULL);
	}
	ft_strlcpy(error_message, "bash: unset: ", ft_strlen("bash: unset: ") + 1);
	ft_strlcat(error_message, invalid_option, ft_strlen(error_message)
		+ ft_strlen(invalid_option) + 1);
	ft_strlcat(error_message, ": invalid option\n", ft_strlen(error_message)
		+ ft_strlen(": invalid option\n") + 1);
	free(invalid_option);
	return (error_message);
}

char *execute_unset(t_cmd *cmd, int *error, t_list *env_lst)
{
	char	*result;
	char	**params;
	int 	i;

	i = 0;
	if (cmd->options)
	{
		*error = 1;
		result = handle_bad_option(cmd->options[0]);
		return (result);
	}
	params = ft_split(cmd->params, ' ');
	while (params[i])
	{
		env_list_remove(&env_lst, params[i]);
		i++;
	}
	return (NULL);
}
