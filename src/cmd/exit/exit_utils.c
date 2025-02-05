/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:14:42 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/05 15:20:57 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*exit_trim_quote_first_option(char *str)
{
	str = ft_strtrim(str, "-\"'");
	str = ft_strjoin("-", str);
	return (str);
}
