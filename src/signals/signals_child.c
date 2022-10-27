/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:38:17 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:05:08 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_DFL;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	child_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_DFL;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	signals_child_process(struct termios *termios_cpy)
{
	reset_echoctl(termios_cpy);
	child_sigint();
	child_sigquit();
}

void	signals_child_heredoc(void)
{
	child_sigint();
	parent_sigquit();
}
