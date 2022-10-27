/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:58:11 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:05:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* After saving string into the node of AST, frees the token input that was 
allocated before*/
void	free_token(void *token)
{
	if (((t_token *)token)->input)
		free(((t_token *)token)->input);
	free(token);
}

/* to existing parent node adds child node, if child node exists - 
assigns incoming to a next sibling */
t_ast	*add_child(t_ast *top, t_ast *child)
{
	t_ast	*sibling;

	if (!top || !child)
		return (NULL);
	if (!top->child)
		top->child = child;
	else
	{
		sibling = top->child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	top->nodes++;
	return (child);
}

void	free_node(t_ast *node)
{
	t_ast	*sibling;
	t_ast	*temp;

	if (node == NULL)
		return ;
	temp = node->child;
	while (temp)
	{
		sibling = temp->next_sibling;
		free_node(temp);
		temp = sibling;
	}
	if (node->cmds != NULL)
		free(node->cmds);
	free(node);
}
