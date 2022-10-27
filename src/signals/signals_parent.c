/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:16:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:04:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	parent_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	signals_parent_process(void)
{
	parent_sigint();
	parent_sigquit();
}
