/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:53:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/27 20:35:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_minus_n(char *s)
{
	if (*s != '-')
		return (false);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (false);
		s++;
	}
	return (true);
}

/* sets newline to false if output should not be followed by a newline, sets it
 * to true if there should be a newline. Returns the index of the first non -n
 * type string in argv. If only -n type options are found, followed by NULL,
 * they should be treated as arguments and thus newline is set to true and i is
 * set back to 1.
 */
int	set_newline(char **argv, bool *newline)
{
	int	i;

	if (!is_minus_n(argv[1]))
	{
		*newline = true;
		return (1);
	}
	i = 2;
	while (argv[i] != NULL && is_minus_n(argv[i]))
		i++;
	if (argv[i] == NULL)
		*newline = true;
	else
		*newline = false;
	return (i);
}

/* checks if echo is called without any arguments, in that case, prints a
 * newline and returns. Calls set_newline to set the newline value (1 in 
 * case a newline should be printed, zero in case no newline should be
 * printed). Cycles through all further arguments and prints them, separated
 * by spaces. Prints a newline after last arguments if newline was set
 * to 1.
 */
void	mini_echo(int argc, char **argv)
{
	bool	newline;
	int		i;

	if (argc == 1)
	{
		write (1, "\n", 1);
		return ;
	}
	i = set_newline(argv, &newline);
	if (argv[i] == NULL)
		return ;
	while (argv[i + 1] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		write(1, " ", 1);
		i++;
	}
	ft_putstr_fd(argv[i], 1);
	if (newline)
		write(1, "\n", 1);
}
