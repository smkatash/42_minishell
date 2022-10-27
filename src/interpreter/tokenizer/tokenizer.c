/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:30:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:07:06 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* initializes the structure of a token and sets all 
values to NULL */
static t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		error_shell("Token not initialized", ERROR_PERROR);
		return (NULL);
	}
	token->input_len = 0;
	token->input = NULL;
	token->type = T_UNKNOWN;
	token->line = NULL;
	return (token);
}

/* sets the current operator symbol that as a peek, in case of
redirection it gets next character to save into the lexing buffer.
If it's not the beginning of lexer ad not redirection, it decrements
the position of the input line.
 */
void	token_operator(t_lexer *lex, t_prompt *line, char c)
{
	char	peek;
	char	temp;

	peek = set_peek(line);
	if (lex->index == 0 && (c == '<' || c == '>'))
	{
		save_to_lexer(lex, c);
		if (((c == '>' && peek == '>') || (c == '<' \
		&& (peek == '>' || peek == '<'))))
		{
			c = get_charbychar(line);
			save_to_lexer(lex, c);
		}
	}
	else if (lex->index == 0 && ((c == '&' && peek == '&') || \
		(c == '|' && peek == '|')))
	{
		save_to_lexer(lex, c);
		temp = get_charbychar(line);
		save_to_lexer(lex, temp);
	}
	else if (lex->index > 0)
		update_char(line);
	else
		save_to_lexer(lex, c);
}

/* compares the operators and input string from lexer, assigns token type in the
token structure */
void	set_token_type(t_token *token, char *lex)
{
	if (!ft_strcmp(lex, "|"))
		token->type = T_PIPE;
	else if (!ft_strcmp(lex, ">"))
		token->type = T_GREAT;
	else if (!ft_strcmp(lex, "<"))
		token->type = T_LESS;
	else if (!ft_strcmp(lex, "<>"))
		token->type = T_LESSGREAT;
	else if (!ft_strcmp(lex, ">>"))
		token->type = T_DGREAT;
	else if (!ft_strcmp(lex, "<<"))
		token->type = T_DLESS;
	else if (!ft_strcmp(lex, "("))
		token->type = T_LBRACE;
	else if (!ft_strcmp(lex, ")"))
		token->type = T_RBRACE;
	else if (!ft_strcmp(lex, "&&"))
		token->type = T_AND;
	else if (!ft_strcmp(lex, "||"))
		token->type = T_OR;
	else if (check_value_assign(lex) && ft_strchr(lex, '='))
		token->type = T_ASSIGN;
	else
		token->type = T_STRING;
}

/* if input from lexer is not empty, runs the get token type 
function and assigns token operators to each string */
t_token	*create_token(t_token *token, t_prompt *line, char *value)
{
	char	*temp;

	if (value == NULL)
	{
		token->type = T_EOF;
		if (line != NULL && line->input != NULL)
			free(line->input);
		return (token);
	}
	temp = ft_strdup(value);
	if (!temp)
	{
		error_shell("Failed to create a token", ERROR_PERROR);
		token->type = T_EOF;
		return (token);
	}
	token->input_len = ft_strlen(value);
	set_token_type(token, value);
	token->input = temp;
	token->line = line;
	return (token);
}

/* Main tokenizer:
1. Initializes token structure;
2. Calls launch token for each string to set token type and string from lexer;
3. With lexer parser, verifies quotation cases with '\"' and "\';
4. Sets NULL termination into the lexer string pointer if lexer is empty.
*/
t_token	*tokenizer(t_lexer *lex, t_prompt *line)
{
	t_token	*token;

	token = init_token();
	if (line == NULL || line->input == NULL)
		return (create_token(token, line, NULL));
	if (lex->tokens == NULL)
		init_buffer(lex);
	if (lex->tokens == NULL)
		return (create_token(token, line, NULL));
	lex->index = 0;
	lex->tokens[0] = '\0';
	lexer_get_value(lex, line);
	if (lex->index == 0)
		return (create_token(token, line, NULL));
	if (lex->index >= lex->len)
		lex->index--;
	lex->tokens[lex->index] = '\0';
	if (token)
		create_token(token, line, lex->tokens);
	return (token);
}
