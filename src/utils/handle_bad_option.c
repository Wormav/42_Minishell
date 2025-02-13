/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bad_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:04:53 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 17:11:27 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*create_error_message(char *cmd_name, char *invalid_option)
{
	char	*error_message;

	error_message = lp_alloc(ft_strlen("minishell: ")
			+ ft_strlen(cmd_name)
			+ ft_strlen(": ")
			+ ft_strlen(invalid_option)
			+ ft_strlen(": invalid option\n") + 1);
	if (!error_message)
		return (NULL);
	return (error_message);
}

char	*handle_bad_option(char *option, char *cmd_name)
{
	char	*error_message;
	char	*invalid_option;

	invalid_option = ft_substr(option, 0, 2);
	if (!invalid_option)
		return (NULL);
	error_message = create_error_message(cmd_name, invalid_option);
	if (!error_message)
	{
		lp_free(invalid_option);
		return (NULL);
	}
	ft_strlcpy(error_message, "minishell: ", ft_strlen("minishell: ") + 1);
	ft_strlcat(error_message, cmd_name, ft_strlen(error_message)
		+ ft_strlen(cmd_name) + 1);
	ft_strlcat(error_message, ": ", ft_strlen(error_message) + 3);
	ft_strlcat(error_message, invalid_option, ft_strlen(error_message)
		+ ft_strlen(invalid_option) + 1);
	ft_strlcat(error_message, ": invalid option\n", ft_strlen(error_message)
		+ ft_strlen(": invalid option\n") + 1);
	lp_free(invalid_option);
	return (error_message);
}
