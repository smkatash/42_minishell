/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:09:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:37:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_redirections_single_builtin(t_exec *exec, t_ast *node, int fd_cpys[2], \
t_minishell *minishell)
{
	exec->cmd_type = node->cmds;
	if (execute_redirection(exec, minishell))
		return (-1);
	if (exec->fd_in > 0)
	{
		fd_cpys[0] = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup(exec->fd_in);
	}		
	if (exec->fd_out > 1)
	{
		fd_cpys[1] = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup(exec->fd_out);
	}
	return (0);
}

void	restore_stdin_stdout_builtin(t_exec *exec, int fd_cpys[2])
{
	if (exec->fd_in > 0)
	{
		close(STDIN_FILENO);
		dup(fd_cpys[0]);
	}
	if (exec->fd_out > 1)
	{
		close(STDOUT_FILENO);
		dup(fd_cpys[1]);
	}
	exec->cmd_type = NULL;
}
