/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:42:54 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:06 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_PIPESPLIT1);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_COMMANDSET);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_pipe1(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_child_node(&node, temp_node, NT_PIPESPLIT);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type);
		node->node->type = N_PIPE;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_subshell(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		temp_node->node->type = N_SUB;
		branch_node(&node, temp_node, T_RBRACE);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_AND_OR);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, T_LBRACE);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}
