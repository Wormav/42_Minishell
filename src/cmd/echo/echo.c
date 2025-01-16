/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:55 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/16 10:39:42 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*env_parsing(t_cmd cmd, char *to_find)
{
	int	i;
	char	*ptr;

	i = 0;
	while (cmd.env[i])
	{
		if (!ft_strncmp(to_find, cmd.env[i], ft_strlen(to_find))
			&& cmd.env[i][ft_strlen(to_find + 1)] == '=')
		{
			ptr = &cmd.env[i][ft_strlen(to_find + 1)];
			return (ptr);
		}
		i++;
	}
	return (NULL);
}

static size_t	__size_var(char *str, int index)
{
	while (str[index] && str[index] != ' ')
		index++;
	return (index);
}

char	*ft_echo(t_cmd cmd, int *error)
{
	int		quote;
	char	*str;


}
