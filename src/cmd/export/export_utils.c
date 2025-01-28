/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:40:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/28 11:57:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_is_valid_key(char *str)
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

static int	check_key_format(char *str)
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
	return (1);
}

int	export_check_params(char *str)
{
	if (!check_key_format(str))
		return (0);
	while (*str && *str != '=')
		str++;
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

int	export_find_next_sign(char sign, char *str)
{
	char	*start;

	start = str;
	str++;
	while (*str && *str != sign)
		str++;
	return (str - start);
}

char	*export_remove_plus_before_equal(char *str)
{
	char	*ret;
	int		i;
	int		j;

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
