/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:20:49 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/27 12:00:00 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_heredoc(char *delim, int *fd, \
	t_exec *exec, t_minishell *shell)
{
	char	*get_line;
	char	*update_line;

	signals_child_heredoc();
	close(fd[0]);
	(void)shell;
	//heredoc_child_helper_destruction(exec, shell);
	update_line = NULL;
	ft_putstr_fd("heredoc> ", 1);
	get_line = get_next_line(STDIN_FILENO);
	while (get_line)
	{
		update_line = ft_substr(get_line, 0, ft_strlen(get_line) - 1);
		if (ft_strcmp(delim, update_line) == 0)
			heredoc_helper_destruction2(delim, 0);
		if (write(fd[1], get_line, ft_strlen(get_line)) == -1)
			error_shell("Failed to write into pipe", ERROR_UNDEFINED);
		heredoc_helper_destruction(&update_line, &get_line, NULL, exec);
		ft_putstr_fd("heredoc> ", 1);
		get_line = get_next_line(STDIN_FILENO);
	}
	heredoc_helper_destruction(&update_line, &get_line, fd, exec);
	heredoc_helper_destruction2(delim, 1);
}

int	execute_heredoc(char *delim, t_exec *exec, t_minishell *shell)
{
	int	status;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_shell("Failed to create a pipe in heredoc", ERROR_PERROR);
	signals_parent_process();
	pid = fork();
	if (pid == -1)
		error_shell(NULL, ERROR_PERROR);
	if (pid == 0)
		child_process_heredoc(delim, fd, exec, shell);
	wait(&status);
	if (!WIFSIGNALED(status))
		g_global_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global_exit_status = 1;
	close(fd[1]);
	if (g_global_exit_status == 0)
		dup2(fd[0], 0);
	else
		exec->fd_in = -1;
	close(fd[0]);
	write(1, "\n", 1);
	return (g_global_exit_status);
}
