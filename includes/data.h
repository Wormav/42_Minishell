/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:13:27 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/06 12:18:49 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
#define DATA_H

typedef struct s_data
{
	int		error_parsing;
	char	*str_prompt;
	long	error;
	int		arr_fd[8192];
} t_data;

#endif
