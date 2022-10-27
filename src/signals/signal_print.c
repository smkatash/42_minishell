/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:27:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:05:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_print(int status)
{
	if (status == SIGINT)
		write(1, "\n", 1);
	if (status == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	if (status == SIGBUS)
		write(1, "Bus error: 10\n", 15);
	if (status == SIGSEGV)
		write(1, "Segmentation fault: 11\n", 24);
}
