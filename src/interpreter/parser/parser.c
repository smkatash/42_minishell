/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:02:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a new node for parser and assigns a token type */
void	*create_node(enum e_grammar tok_type)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->token_type = tok_type;
	node->node_type = N_DUMM;
	node->node = NULL;
	return ((void *)node);
}

/* if node type is command, assignment or redirection, function creates 
a list of each type and saves into the node */
void	add_nodes_parser(t_list **tokens, t_parser *node_p, t_list **cmd)
{
	if (node_p->node && !node_p->node->cmds && \
	(node_p->node_type == N_CMD || node_p->node_type == N_ASSIGN \
	|| node_p->node_type == N_REDIR))
	{
		node_p->node->cmds = malloc(sizeof(t_cmd_def));
		node_p->node->cmds->cmd = NULL;
		node_p->node->cmds->assign = NULL;
		node_p->node->cmds->redir = NULL;
	}
	if (node_p->node_type == N_CMD)
		ft_lstadd_back(&node_p->node->cmds->cmd, \
		ft_lstnew(ft_strdup(((t_token *)(*tokens)->content)->input)));
	if (node_p->node_type == N_ASSIGN)
		ft_lstadd_back(&node_p->node->cmds->assign, \
		ft_lstnew(ft_strdup(((t_token *)(*tokens)->content)->input)));
	if (node_p->node_type == N_REDIR)
		ft_lstadd_back(&node_p->node->cmds->redir, \
		ft_lstnew(ft_strdup(((t_token *)(*tokens)->content)->input)));
	*tokens = (*tokens)->next;
	free(lst_get_content(cmd));
}

/* scans node type and calls the production of nodes according
to ll1 table, if nodes token type is not valid returns the flag zero*/
int	scan_nodes_parser(t_list *token_list, t_parser *node_p, \
t_list **cmds, void (***table)(t_list **, enum e_grammar))
{
	int				flag;
	void			(*tab)(t_list **, enum e_grammar);
	enum e_grammar	token_type;

	flag = 1;
	tab = NULL;
	token_type = ((t_token *)token_list->content)->type;
	if (node_p->token_type < NONTERM)
	{
		tab = *table[node_p->token_type][token_type - NONTERM];
	}
	if (tab)
		tab(cmds, ((t_token *)token_list->content)->type);
	else
		flag = 0;
	if (!flag)
	{
		while (ft_lstsize(*cmds) > 0)
			free(lst_get_content(cmds));
	}
	return (flag);
}

/* Through the syntax check with a given grammar table, parser launches 
the tree:
1. initialzes the parser structure;
2. scans the nodes and token lists into temporary table and compares/verifies 
existing tokens with grammar table;
3. add nodes if node of commands, assignment or redirection is found;
4. in case of error, frees the node of a tree */
t_ast	*check_syntax(t_list *token_list, void (***table) \
	(t_list **, enum e_grammar))
{
	t_ast		*node;
	t_parser	*node_p;
	t_list		*cmds;
	int			flag;

	init_parser(&cmds, &node);
	flag = 1;
	while (flag && ft_lstsize(cmds) > 0)
	{
		node_p = (t_parser *)lst_get_cmd(cmds);
		if (((t_token *)token_list->content)->type == node_p->token_type)
			add_nodes_parser(&token_list, node_p, &cmds);
		else
			flag = scan_nodes_parser(token_list, node_p, &cmds, table);
	}
	if (!flag)
	{
		parsing_syntax_error(((t_token *)token_list->content)->input);
		free_ast_tree(&node);
	}
	remove_ast_node(&node);
	return (node);
}
