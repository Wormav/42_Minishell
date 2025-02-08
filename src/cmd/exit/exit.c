/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:01:46 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/06 21:45:26 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <minishell.h>

static char	*handle_bad_params(char *option)
{
	char	*error_message;
	char	*space_pos;

	error_message = lp_alloc(ft_strlen("bash: exit: ")
			+ ft_strlen(option)
			+ ft_strlen(": numeric argument required\n") + 1);
	if (!error_message)
		return (NULL);
	ft_strlcpy(error_message, "bash: exit: ", ft_strlen("bash: exit: ") + 1);
	ft_strlcat(error_message, option, ft_strlen(error_message)
		+ ft_strlen(option) + 1);
	space_pos = ft_strchr(option, ' ');
	if (space_pos)
		*space_pos = '\0';
	ft_strlcat(error_message, ": numeric argument required\n",
		ft_strlen(error_message)
		+ ft_strlen(": numeric argument required\n") + 1);
	return (error_message);
}

static int	content_valid_code(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (str[0] == '-' && str[1] == '-' && str[2] == '\0')
		return (1);
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && sign)
			return (0);
		if (!ft_isdigit(str[i]) && (str[i] != '-' && str[i] != '+'))
			return (0);
		if (str[i] == '-' || str[i] == '+')
			sign++;
		i++;
	}
	return (1);
}

static int	handle_option_errors(t_cmd *cmd)
{
	if (cmd->options)
	{
		cmd->options[0] = exit_trim_quote_first_option(cmd->options[0]);
		if (cmd->options[1] || (cmd->options[0] && cmd->params[0] != 0))
		{
			printf("bash: exit: too many arguments\n");
			return (1);
		}
		else if (!content_valid_code(cmd->options[0]))
		{
			printf("%s", handle_bad_params(cmd->options[0]));
			return (2);
		}
	}
	return (0);
}

static int	handle_exit_errors(t_cmd *cmd, int *overflow_error)
{
	char	**params;
	int		result;

	params = NULL;
	result = handle_option_errors(cmd);
	if (result != 0)
		return (result);
	if (cmd->params && cmd->params[0] != 0)
		params = ft_split(cmd->params, ' ');
	if (params && params[0])
	{
		if ((!ft_atol(params[0], overflow_error) && *overflow_error)
			|| !content_valid_code(params[0]))
		{
			ft_putstr_fd(handle_bad_params(params[0]), 2);
			return (2);
		}
	}
	if ((cmd->options && params && params[0]) || (params && params[1]))
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

void	execute_exit(t_cmd *cmd, t_data *data, int *flag)
{
	int		error_exit;
	int		overflow_error;

	if (*flag == 1)
		return ;
	error_exit = handle_exit_errors(cmd, &overflow_error);
	if (error_exit)
	{
		data->error = error_exit;
		if (error_exit == 2)
			data_close_and_exit(data, 2);
		return ;
	}
	if (cmd->options)
		data->error = ft_atol(cmd->options[0], &overflow_error);
	else
		data->error = ft_atol(cmd->params, &overflow_error);
	if (error_exit != 1)
		data_close_and_exit(data, data->error);
	return ;
}
