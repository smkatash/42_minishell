/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:46:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/27 17:42:35 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exit_is_valid(char *arg)
{
	while (*arg == ' ' || *arg == '\t')
		arg++;
	if (*arg == '\0')
		return (false);
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!ft_isdigit(*arg))
		return (false);
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			break ;
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	if (*arg == '\0')
		return (true);
	while (*arg == ' ' || *arg == '\t')
		arg++;
	if (*arg == '\0')
		return (true);
	return (false);
}

void	mini_exit(int argc, char **argv, t_minishell *minishell)
{
	bool	valid;

	if (argc > 1)
	{
		valid = exit_is_valid(argv[1]);
		if (valid)
			g_global_exit_status = (int)((unsigned char)ft_atoi(argv[1]));
		else
			g_global_exit_status = 255;
	}
	ft_putstr_fd("exit\n", 1);
	if (argc > 1 && !valid)
	{
		print_error("exit", argv[1], NULL, -1);
		ft_putstr_fd("numeric argument required\n", 2);
	}
	free_minishell(minishell);
	free(argv);
	reset_echoctl(&(minishell->termios_cpy));
	//system("leaks minishell");
	exit(g_global_exit_status);
}
