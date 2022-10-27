/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interactive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:32:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:05:03 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_newline(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_global_exit_status = 1;
	}
}

void	sigquit_interactive(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	sigint_interactive(void)
{
	struct sigaction	sn;

	sn.sa_handler = &display_newline;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	signals_interactive_mode(struct termios *termios_cpy)
{
	cancel_echoctl(termios_cpy);
	sigint_interactive();
	sigquit_interactive();
}
