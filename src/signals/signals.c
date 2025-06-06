/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:10:13 by jlorette          #+#    #+#             */
/*   Updated: 2025/02/13 16:54:57 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_fork(__attribute__((unused)) int sig)
{
	extern int	g_ack;

	if (sig == SIGINT)
	{
		g_ack = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_ack = 131;
		write(1, "Quit\n", 5);
	}
}

void	handle_sigint(__attribute__((unused)) int sig)
{
	extern int	g_ack;

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ack = 130;
}
