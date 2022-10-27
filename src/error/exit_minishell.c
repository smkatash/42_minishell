/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:36:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:07:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell)
	{
		free(minishell->line);
		clear_env(&(minishell->env));
		if (minishell->table)
			free_syntax_table(minishell->table);
	}
}

void	exit_minishell(int flag, int PHASE, char *error, t_minishell *minishell)
{
	free_minishell(minishell);
	if (PHASE == INIT)
		print_error("Unable to initialize minishell", NULL, NULL, flag);
	else
		print_error(error, NULL, NULL, flag);
	error_set_global_exit_status(flag);
	exit(g_global_exit_status);
}
