/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:15:57 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks for token, if pipe, and, or operators are found it sets cmd 
value to zero, if type is string - recognized as cmd. If previous type 
was string, current assignment is changed into type string */
void	type_checker(t_token *tok, int *is_balanced, int *cmd_flag)
{
	if (*is_balanced)
		*is_balanced = quote_checker(tok->input);
	if (tok->type == T_STRING)
		*cmd_flag = 1;
	if (tok->type == T_AND || tok->type == T_OR || tok->type == T_PIPE)
		*cmd_flag = 0;
	if (tok->type == T_ASSIGN && *cmd_flag)
		tok->type = T_STRING;
}

/* loops over the lexer and adds token structure into
the linked list. In case of, check flag failure, it cleans the list */
t_list	*get_token_list(t_lexer *lex, t_prompt *line)
{
	t_list	*token_list;
	t_token	*token;
	int		cmd_found;
	int		quotes_flag;

	token_list = NULL;
	token = tokenizer(lex, line);
	cmd_found = 0;
	quotes_flag = 1;
	while (token->type != T_EOF)
	{
		type_checker(token, &quotes_flag, &cmd_found);
		ft_lstadd_back(&token_list, ft_lstnew(token));
		token = tokenizer(lex, line);
	}
	ft_lstadd_back(&token_list, ft_lstnew(token));
	if (!quotes_flag)
		ft_lstclear(&token_list, &delete_token);
	return (token_list);
}

/*
initializes the structure of a lexer and sets all 
values to NULL. It has:
- token as a string;
- length af a token;
- index of current position.
 */
t_lexer	*init_lexer(void)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	lex->len = 0;
	lex->index = -1;
	lex->tokens = NULL;
	return (lex);
}

/*
creates a structure for lexer, gets a list of tokens retrieved char by char
the input line and returns a list of tokens
*/
t_list	*lexer(t_prompt *line)
{
	t_list	*tokens;
	t_lexer	*lex;

	lex = init_lexer();
	tokens = get_token_list(lex, line);
	free(lex->tokens);
	free(lex);
	return (tokens);
}
