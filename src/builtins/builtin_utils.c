/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:11:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/27 22:36:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*get_ast_node(t_exec *exec)
{
	t_list		*cmds_list;

	if (exec != NULL && exec->cmds_list != NULL)
	{
		cmds_list = *(exec->cmds_list);
		if (cmds_list != NULL)
			return ((t_ast *)(cmds_list->content));
	}
	return (NULL);
}

void	free_single_builtin(t_exec *exec, t_ast *node)
{
	free(*(exec->cmds_list));
	free_cmd_defs(&node->cmds);
	free(node);
}
