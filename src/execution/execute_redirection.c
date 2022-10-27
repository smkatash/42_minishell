/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:24:26 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/27 11:19:58 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_redirect_in(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 0)
		close(*fd);
	if (file)
	{
		*fd = open(file, O_RDONLY);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		error_shell(file, ERROR_PERROR);
	return (status);
}

static int	execute_redirect_overwrite(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 1)
		close(*fd);
	if (file)
	{
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		error_shell(file, ERROR_PERROR);
	return (status);
}

static int	execute_redirect_append(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 1)
		close(*fd);
	if (file)
	{
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		error_shell(file, ERROR_PERROR);
	return (status);
}

static int	execute_redirect_inout(char *file, int	*fd_in, int *fd_out)
{
	int	status;

	status = 0;
	if (file)
	{
		if (*fd_out > 1)
			close(*fd_out);
		*fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (*fd_out > 1)
			close(*fd_out);
		*fd_in = open(file, O_RDONLY);
	}
	if (*fd_out < 0 || *fd_in < 0)
	{
			status = 1;
			g_global_exit_status = status;
	}
	if (status)
		error_shell(file, ERROR_PERROR);
	return (status);
}

int	execute_redirection(t_exec *exec, t_minishell *minishell)
{
	t_list	*redir;
	char	*file;
	int		status;
	int		here_doc[2];

	status = 0;
	update_redir(exec, &redir, here_doc);
	while (redir && status == 0)
	{
		status = get_redirect_file(&redir->next, &file, here_doc[1]);
		if (!status && ft_strcmp((char *)redir->content, "<") == 0)
			status = execute_redirect_in(file, &exec->fd_in);
		else if (!status && ft_strcmp((char *)redir->content, ">") == 0)
			status = execute_redirect_overwrite(file, &exec->fd_out);
		else if (!status && ft_strcmp((char *)redir->content, ">>") == 0)
			status = execute_redirect_append(file, &exec->fd_out);
		else if (!status && ft_strcmp((char *)redir->content, "<<") == 0)
			status = redirect_here_doc(file, here_doc[0], exec, minishell);
		else if (!status && ft_strcmp((char *)redir->content, "<>") == 0)
			status = execute_redirect_inout(file, &exec->fd_in, &exec->fd_out);
		if (redir->next)
			redir = redir->next->next;
	}
	return (status);
}
