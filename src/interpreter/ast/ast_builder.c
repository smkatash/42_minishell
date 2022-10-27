/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:10:51 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:05:48 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes the prompt structure by saving the input line */
static void	copy_input_line(t_prompt *line, char *readline)
{
	line->input = ft_strdup(readline);
	line->len = ft_strlen(readline);
	line->index = -2;
}

/* AST builder:
1. initializes the content and saves input line into t_prompt 
structure;
2. calls lexer function to receieve a list of tokens;
3. if a list of tokens exist, parses through syntax check is called;
Syntax check implements creation of nodes depending on the grammar 
and list of tokens.
*/
t_ast	*ast_builder(char *input, void (***table)(t_list **, enum e_grammar))
{
	t_prompt	content;
	t_ast		*node;
	t_list		*token_list;

	node = NULL;
	copy_input_line(&content, input);
	token_list = lexer(&content);
	if (token_list != NULL)
	{
		node = check_syntax(token_list, table);
		ft_lstclear(&token_list, &free_token);
	}
	return (node);
}
