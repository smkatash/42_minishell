/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:25:08 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_to_file(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, T_STRING);
		node->node_type = N_REDIR;
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type),
		node->node_type = N_REDIR;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_redirections(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_REDIR1);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, NT_IO_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_redirections1(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_io_file(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		if (type == T_DLESS)
			branch_node(&node, temp_node, NT_IO_HERE);
		else
			branch_node(&node, temp_node, NT_IO_FILE);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_io_here(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, T_STRING);
		node->node_type = N_REDIR;
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, T_DLESS);
		node->node_type = N_REDIR;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}
