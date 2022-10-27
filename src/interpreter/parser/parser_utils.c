/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:45:15 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes a new node and assigns a node type to it*/
t_ast	*init_new_node(enum e_node_type n_type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = n_type;
	node->cmds = NULL;
	node->nodes = 0;
	node->child = NULL;
	node->prev_sibling = NULL;
	node->next_sibling = NULL;
	return (node);
}

/* Initializes parses by setting up the list of commands and 
launching the start of the node for the AST */
void	init_parser(t_list **cmds_list, t_ast **node)
{
	*cmds_list = NULL;
	*node = init_new_node(N_DUMM);
	ft_lstpush(cmds_list, create_node(T_EOF));
	ft_lstpush(cmds_list, create_node(NT_START));
	((t_parser *)(*cmds_list)->content)->node = *node;
}

/* frees one node at a time if it is not a subshell, has only one node left*/
void	remove_ast_node(t_ast **node)
{
	t_ast	*temp;

	if (*node != NULL)
	{
		remove_ast_node(&(*node)->next_sibling);
		remove_ast_node(&(*node)->child);
	}
	if (*node != NULL && (*node)->type != N_SUB && (*node)->nodes == 1)
	{
		temp = *node;
		*node = (*node)->child;
		(*node)->next_sibling = temp->next_sibling;
		(*node)->prev_sibling = temp->prev_sibling;
		free (temp);
	}
}

/*frees list of commands from the node */
void	free_ast_commands(t_cmd_def **cmds)
{
	if (*cmds == NULL)
		return ;
	if ((*cmds)->cmd)
		ft_lstclear(&((*cmds)->cmd), &free);
	if ((*cmds)->redir)
		ft_lstclear(&((*cmds)->redir), &free);
	if ((*cmds)->assign)
		ft_lstclear(&((*cmds)->assign), &free);
	free(*cmds);
	*cmds = NULL;
}

/* frees AST node by node */
void	free_ast_tree(t_ast **ast)
{
	if ((*ast) == NULL)
		return ;
	free_ast_tree(&(*ast)->child);
	free_ast_tree(&(*ast)->next_sibling);
	free_ast_commands(&(*ast)->cmds);
	free(*ast);
	*ast = NULL;
}
