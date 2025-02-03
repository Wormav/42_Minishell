/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:29:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/03 16:05:42 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <token.h>
# include <ast.h>
# include <cmd.h>

void	clean_memory(t_ast *ast, t_token *token, char *str);
void	free_split(char **split);
long	ft_atol(char *nptr, int *overflow_error);
char	*handle_bad_option(char *option, char *cmd_name);
int		has_equal_sign(char *str);
char	*ft_ltoa(long n);
void	cmd_filter_params(t_cmd **cmd);
int		count_params_size(char *params);

#endif
