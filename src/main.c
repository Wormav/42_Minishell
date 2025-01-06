/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:37:21 by stetrel           #+#    #+#             */
/*   Updated: 2025/01/06 09:59:59 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <token.h>
#include <debug.h>

int	main(int argc, char **argv)
{
	char	*str;
	t_token	*list;

	if (argc != 2)
		return (1);
	str = ft_strdup(argv[1]);
	list = NULL;
	list = parse_string(str);
	print_token_list(list);
	free_token(list);
	free(str);
}
