/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:27:43 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/28 20:42:09 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wildcard_expander(t_list **cmds)
{
	int	status;

	status = 0;
	filename_expansion(cmds);
	if (ft_lstsize(*cmds) > 512)
	{
		expansion_error((char *)(*cmds)->content, ERROR_CMD);
		status = 1;
	}
	return (status);
}

static int	child_process(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	int	status;

	status = 0;
	signals_child_process(&(minishell->termios_cpy));
	status = wildcard_expander(&cmd->cmd);
	if (exec->fd_in >= 0 && exec->fd_out > 0)
		status = run_cmd_child(exec, cmd, minishell);
	else
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
		free_cmd_defs(&cmd);
		free_minishell(minishell);
		if (exec->fd_in < 0 || exec->fd_out < 0)
			exit(g_global_exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	return (status);
}

static void	parent_process(t_exec *exec, t_cmd_def *cmd)
{
	t_ast	*node;

	signals_parent_process();
	node = lst_get_cmd(*exec->cmds_list);
	if (ft_lstsize(*exec->cmds_list) && cmd && cmd->cmd && \
		node->type != N_AND && node->type != N_OR && \
		(!ft_strstr((char *)cmd->cmd->content, "cat") && node->type == N_REDIR))
	{
		waitpid(exec->pid, NULL, 0);
	}
	else
		waitpid(exec->pid, NULL, 1);
	close(exec->pipe_fd[1]);
	if (exec->fd_in > 0)
		close(exec->fd_in);
}

int	fork_process(t_exec *exec_cmds, t_cmd_def *cmds, t_minishell *minishell)
{
	int	status;

	if (cmds->cmd == NULL)
		return (0);
	status = 0;
	if (pipe(exec_cmds->pipe_fd) == -1)
		return (error_shell("Failed to create a pipe", ERROR_PERROR));
	exec_cmds->pid = fork();
	if (exec_cmds->pid == -1)
		status = error_shell("Failed to create a pipe", ERROR_PERROR);
	exec_cmds->forks = 1;
	if (exec_cmds->pid == 0 && status == 0)
		status = child_process(exec_cmds, cmds, minishell);
	parent_process(exec_cmds, cmds);
	return (status);
}
