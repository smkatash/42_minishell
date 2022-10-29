/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:36:16 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/29 20:46:54 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get nodes from tree into the ordered linked lists */
void	get_tree(t_list **nodes, t_ast *tree, int node_id)
{
	if (!tree)
		return ;
	tree->node_id = node_id;
	if (tree->child)
		get_tree(nodes, tree->child->next_sibling, node_id + 1);
	if (tree->type != N_SUB)
		ft_lstpush(nodes, tree);
	get_tree(nodes, tree->child, node_id + 1);
	if (tree->type == N_SUB)
		ft_lstpush(nodes, tree);
}

/*
- extract the next node to check if there is pipe, if so set the pipe flag
- update the list of cmds
- check if there is a builtin and call the builtin function
- if not builtin - call simple cmd black function
*/
void	execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, \
	t_minishell *minishell)
{
	t_ast	*temp;

	exec_cmds->pipe = 0;
	temp = (t_ast *)lst_get_cmd(*exec_cmds->cmds_list);
	if (temp && temp->type == N_PIPE)
		exec_cmds->pipe = 1;
	execute_cmd_block(exec_cmds, *node, minishell);
	*node = NULL;
}

void	free_file_redirection(char *file, int *here_doc)
{
	if (here_doc[1] != 0)
		free(file);
}
