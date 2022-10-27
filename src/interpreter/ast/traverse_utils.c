/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:16:34 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:05:53 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* creates new node and initializes it to default null */
void	*create_new_node(enum e_grammar tok_type)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	node->token_type = tok_type;
	node->node_type = N_DUMM;
	node->node = NULL;
	return ((void *)node);
}

/* adds a new node into old node and sets the node type */
void	branch_node(t_parser **new_node, t_parser *old_node, int node_type)
{
	*new_node = create_new_node(node_type);
	(*new_node)->node = old_node->node;
}

/* creates a new node, transforms it into child node and links it with 
the next sibling */
void	*branch_child_node(t_parser **new_node, t_parser *prev_node, int type)
{
	t_ast	*sibling;
	void	*new_temp;

	*new_node = create_new_node(type);
	new_temp = init_new_node(N_DUMM);
	sibling = add_child(prev_node->node, new_temp);
	(*new_node)->node = sibling;
	return (sibling);
}

/* retrieves the data from the linked list and frees the list where the data 
was stored */
void	*lst_get_content(t_list **lst)
{
	void	*content;
	t_list	*temp;

	content = NULL;
	if (lst && *lst)
	{
		temp = (*lst)->next;
		content = (*lst)->content;
		free(*lst);
		*lst = temp;
	}
	return (content);
}

/* if list exists, return the data of a list */
void	*lst_get_cmd(t_list *cmd)
{
	if (cmd)
	{
		return (cmd->content);
	}
	return (NULL);
}
