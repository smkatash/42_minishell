/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:18:47 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/27 01:21:33 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child_helper_destruction(t_exec *exec_cmds, t_minishell *shell)
{
	free_minishell(shell);
	free_ast_node(exec_cmds->cmds_list);
	free_cmd_defs(&exec_cmds->cmd_type);
}

void	heredoc_helper_destruction(char **update, char **line, int *fd, \
	t_exec *exec_cmds)
{
	if (fd)
	{
		close(fd[1]);
		if (exec_cmds->curr_cmd)
			free(exec_cmds->curr_cmd);
		free_cmd_defs(&exec_cmds->cmd_type);
		free_ast_node(exec_cmds->cmds_list);
	}
	free(*line);
	*line = NULL;
	free(*update);
	*update = NULL;
}

void	heredoc_helper_destruction2(char *delim, int status)
{
	if (delim[0] != '*')
		free(delim);
	exit(status);
}

void	free_expansion_file(t_expansion *file)
{
	if (file->file)
		free(file->file);
	file->file = NULL;
	free(file);
}

void	free_expansion_file_struct(void *content)
{
	free_expansion_file((t_expansion *)content);
}
