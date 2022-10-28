/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:46:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/28 17:49:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *arg, char *message)
{
	print_error("exit", arg, NULL, -1);
	ft_putstr_fd(message, 2);
}

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

void	space_and_sign(const char *str, int *sign, int *i)
{
	int	index;

	index = 0;
	*sign = 1;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] && (str[index] == '+' || str[index] == '-'))
	{
		if (str[index] == '-')
			*sign = -1;
		index++;
	}
	*i = index;
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	nb;
	long long	nb_previous;
	int			sign;

	if (str == NULL)
		return (0);
	space_and_sign(str, &sign, &i);
	nb = 0;
	nb_previous = 0;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + ((str[i]) - '0');
		if (nb < nb_previous)
		{
			if (ft_strcmp(str, LLONG_MIN_STR) == 0)
				return (LLONG_MIN);
			error_exit(str, EARG_NONNUM);
			return (255);
		}
		nb_previous = nb;
		i++;
	}
	return (nb * sign);
}

void	mini_exit(int argc, char **argv, t_minishell *minishell)
{
	bool	error;

	error = false;
	if (argc > 1)
	{
		if (exit_is_valid(argv[1]) == true)
			g_global_exit_status = (unsigned char)ft_atoll(argv[1]);
		else
		{
			error_exit(argv[1], EARG_NONNUM);
			g_global_exit_status = 255;
			error = true;
		}
	}
	if (argc > 2 && error == false)
	{
		error_exit(NULL, EARG_TOOMANY);
		g_global_exit_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	ft_freestrarr(&argv);
	free_minishell(minishell);
	reset_echoctl(&(minishell->termios_cpy));
	exit(g_global_exit_status);
}
