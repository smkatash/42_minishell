/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:05:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isempty(char *buf)
{
	int	i;

	if (*buf == '\0')
		return (true);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] != ' ' && buf[i] != '\t')
			return (false);
	}
	return (true);
}

/* general structure for minishell main function. Kany, I will 
 * clean this up when time comes ;-) Also, I pass now my t_env
 * struct to everywhere, but in the end we will of course pass
 * one general minishell struct in which we insert t_env.
 * I will adapt it.
 */
	// (void)argc;
	// (void)argv;
int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	g_global_exit_status = 0;
	init_minishell(&minishell, envp);
	buf = NULL;
	while (1)
	{
		signals_interactive_mode(&(minishell.termios_cpy));
		free(buf);
		buf = readline("Minishell>>> ");
		if (buf == NULL)
			break ;
		if (isempty(buf))
			continue ;
		main_executor(buf, &minishell);
		add_history(buf);
	}
	clear_history();
	mini_exit(0, NULL, &minishell);
}
