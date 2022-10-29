/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:58:18 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/29 00:34:40 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_functions(t_minishell *minishell, t_cmd_def *cmd)
{
	free_minishell(minishell);
	free_cmd_defs(&cmd);
}

static void	free_env(t_exec *exec, char **envp, char *path)
{
	ft_freestrarr(&exec->curr_cmd);
	ft_freestrarr(&envp);
	free(path);
}

int	run_cmd_child(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	char	**envp;
	char	*path;

	close(exec->pipe_fd[0]);
	if (!builtin_child_process(exec, cmd, minishell))
	{		
		exec->curr_cmd = list_to_argv(cmd->cmd, NULL);
		envp = make_envp(minishell->env);
		path = find_path(exec->curr_cmd[0], minishell->env);
		free_functions(minishell, cmd);
		if (exec->curr_cmd != NULL && envp != NULL && path != NULL)
		{
			duplicate_fd(exec);
			if (execve(path, exec->curr_cmd, envp) == -1)
			{
				error_shell("failed to execute", ERROR_PERROR);
				g_global_exit_status = EXIT_CANNOT_EXECUTE;
			}
		}
		free_env(exec, envp, path);
	}
	if (exec->fd_in > 0)
		close(exec->fd_in);
	close(exec->pipe_fd[1]);
	exit(g_global_exit_status);
}
