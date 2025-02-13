/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:01:05 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 17:14:14 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_quotes(const char *str, int *i)
{
	char	quote;
	int		only_spaces;
	int		space_count;

	quote = str[*i];
	only_spaces = 1;
	space_count = 0;
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (str[*i] != ' ')
			only_spaces = 0;
		if (str[*i] == ' ')
			space_count++;
		(*i)++;
	}
	if (only_spaces)
		return (space_count);
	if (str[*i])
		(*i)++;
	return (0);
}

static int	is_invalid_params(const char *str)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			space_count = check_quotes(str, &i);
			if (space_count)
				return (space_count);
		}
		else
			i++;
	}
	return (0);
}

char	*create_string_spaces_error(int nbr_spaces)
{
	char	*error;
	int		i;

	i = 0;
	error = lp_alloc(sizeof(char) * (nbr_spaces + 1));
	while (i <= nbr_spaces)
	{
		error[i] = ' ';
		i++;
	}
	error[i] = '\0';
	return (error);
}

int	print_error_params(t_cmd *cmd, long *error)
{
	int		error_code;
	char	*string_error;

	error_code = is_invalid_params(cmd->params);
	if (error_code == 0)
		return (0);
	if (error_code == -1)
		ft_printf(2, "%s: '': No such file or directory\n", cmd->cmd);
	else
	{
		string_error = create_string_spaces_error(error_code);
		ft_printf(2, "%s: cannot access '%s': No such file or directory\n",
			cmd->cmd, string_error);
		lp_free(string_error);
	}
	*error = 2;
	return (1);
}
