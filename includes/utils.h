/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:29:24 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/21 15:35:13 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <token.h>
# include <ast.h>
# include <cmd.h>

typedef struct s_space_state
{
	char	*result;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;
}	t_space_state;

void	clean_memory(t_ast *ast, t_token *token, char *str);
void	free_split(char **split);
long	ft_atol(char *nptr, int *overflow_error);
char	*handle_bad_option(char *option, char *cmd_name);
int		has_equal_sign(char *str);
char	*ft_ltoa(long n);
void	cmd_filter_params(t_cmd **cmd);
int		count_params_size(char *params);
void	save_return_val(t_data *data, t_env **env_lst);
int		check_heredoc(t_token *list);
void	trunc_orders_fds(t_fds *fds, t_data *data);
char	**split_export(char const *str);
void	exit_and_clear_history(long exit_code);
char	*filter_tab(char *str);
char	*reduce_spaces(char *str);

#endif
