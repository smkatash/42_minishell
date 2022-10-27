/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 08:32:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:23 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* from the source string reads character by character and updates the prompt 
structure that holds information of the input. In case of an error, returns 
error code CHAR_ERR 2 */
char	get_charbychar(t_prompt *line)
{
	char	c;

	if (line == NULL || line->input == NULL)
		return (CHAR_ERR);
	if (line->index == -2)
		line->index = -1;
	if (++line->index >= line->len)
	{
		line->index = line->len;
		return (EOL);
	}
	c = line->input[line->index];
	return (c);
}

/* gets the character for the curret index
poisition of input line and returns as a peek
char to token operator */
char	set_peek(t_prompt *line)
{
	char	c;
	long	index;

	if (line == NULL || line->input == NULL)
		return (CHAR_ERR);
	index = line->index;
	if (index == -2)
		index++;
	index++;
	if (index >= line->len)
		return (EOL);
	c = line->input[index];
	return (c);
}

/* updates the position of index in source input line.
Called by token operator */
void	update_char(t_prompt *line)
{
	if (line->index < 0)
		return ;
	else
		line->index--;
}

/* skips whitespace by looping char by char*/
void	skip_whitespace(t_prompt *line)
{
	char	c;

	if (line == NULL || line->input == NULL)
		return ;
	c = set_peek(line);
	while (c != EOL && (c == ' ' || c == '\t'))
		c = get_charbychar(line);
}
