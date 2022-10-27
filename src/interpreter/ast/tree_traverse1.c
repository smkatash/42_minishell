/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:21:22 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:05:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_start(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_AND_OR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_and_or(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_AND_OR1);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_PIPESPLIT);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_and_or1(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		if (type == T_OR)
			temp_node->node->type = N_OR;
		else
			temp_node->node->type = N_AND;
		branch_child_node(&node, temp_node, NT_AND_OR);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type);
		node->node_type = temp_node->node->type;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	set_epsilon(t_list **stack_table, enum e_grammar type)
{
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		free(temp_node);
	}
}
