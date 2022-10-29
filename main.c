/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/29 17:46:43 by ktashbae         ###   ########.fr       */
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
