/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:41:05 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:35:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_node(t_list **node)
{
	t_ast	*temp_node;
	t_list	*lst_node;

	if (node && *node)
	{
		lst_node = *node;
		while (ft_lstsize(lst_node))
		{
			temp_node = (t_ast *)lst_get_content(&lst_node);
			if (temp_node->cmds)
				free_cmd_defs(&temp_node->cmds);
			free(temp_node);
		}
		*node = NULL;
	}
}

static void	free_ast_recurs(t_ast **node)
{
	if (!(*node))
		return ;
	free_ast_recurs(&(*node)->child);
	free_ast_recurs(&(*node)->next_sibling);
	free_cmd_defs(&(*node)->cmds);
	free(*node);
	*node = NULL;
}

void	free_full_ast(t_ast **ast)
{
	free_ast_recurs(ast);
	*ast = NULL;
}

void	free_cmd_defs(t_cmd_def **cmds)
{
	if (*cmds)
	{
		if ((*cmds)->cmd)
			ft_lstclear(&((*cmds)->cmd), &free);
		if ((*cmds)->redir)
			ft_lstclear(&((*cmds)->redir), &free);
		if ((*cmds)->assign)
			ft_lstclear(&((*cmds)->assign), &free);
		free(*cmds);
		*cmds = NULL;
	}
}

void	free_syntax_table(void (***table)(t_list **, enum e_grammar))
{
	int	col;

	col = 0;
	while (col < NONTERM)
	{
		free((table)[col]);
		col++;
	}
	free(table);
}
