/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:48:03 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 21:41:04 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_end_of_key(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}

/* converts g_global_exit_status to string (ft_itoa) and copies
 * this string to the char buffer. In case malloc fails, sets global exit status,
 * frees buffer and sets it to NULL, so that no further expansion will happen.
 */
void	expand_global_exit_status(t_char_buf *buf)
{
	char	*nbr;

	nbr = ft_itoa(g_global_exit_status);
	if (nbr == NULL)
	{
		g_global_exit_status = ENOMEM;
		ft_putstr_fd("minishell: failed to expand exit status\
(faild to allocate memory)\n", 2);
		free(buf->buf);
		buf->buf = NULL;
		return ;
	}
	add_str_to_buf(buf, nbr);
	free(nbr);
}

/*if dollar sign is followed by question mark, expands to the ms_exit global
 * variable. Else, key is set to the first byte after the dollar sign and
 * the end of the key is searched for and set to nul (the original char is 
 * saved in temp and restored afterwards). find_value is called to find the 
 * value to the key and the result is added to the buffer. A pointer to the 
 * first byte after the key is returned
 */
char	*expand_substr_ds(t_env *env, t_char_buf *buf, char *ptr)
{
	char	*key;
	char	*end_of_key;
	char	temp;

	key = ptr + 1;
	if (*key == '?')
	{	
		expand_global_exit_status(buf);
		return (key + 1);
	}
	end_of_key = key;
	while (*end_of_key)
	{
		if (is_end_of_key(*end_of_key))
			break ;
		end_of_key++;
	}
	temp = *end_of_key;
	*end_of_key = '\0';
	add_str_to_buf(buf, find_value(env, key));
	*end_of_key = temp;
	return (end_of_key);
}

/* if a dollarsign is found, checks if it should be expanded. If not,
 * adds dollarsign to buffer, moves ptr passed dollarsign and returns false.
 * Returns true if the dollar sign should indeed be expanded.
 */
static bool	should_be_expanded(char **ptr, t_char_buf *buf, int quotes)
{
	char	next_char;

	next_char = *(*ptr + 1);
	if (next_char == '\0')
	{
		add_char_to_buf(buf, **ptr);
		(*ptr)++;
		return (false);
	}
	if (next_char == '\'' || next_char == '\"')
	{
		if (quotes == DOUBLE_QUOTES)
			add_char_to_buf(buf, **ptr);
		(*ptr)++;
		return (false);
	}
	if (next_char == '$')
	{
		add_str_to_buf(buf, "$$");
		(*ptr) += 2;
		return (false);
	}
	return (true);
}

/* copies string into buffer in t_char_buf struct. Sets the buffer to NULL if
 * malloc fails somewhere along the way. 
 * expands dollar signs when needed (depending on quotes, environment variables
 * and following dollarsigns)
 */
void	expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf)
{
	int			quotes;

	if (buf->buf == NULL)
		return ;
	quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr == '$' && quotes != SINGLE_QUOTES)
		{
			if (should_be_expanded(&ptr, buf, quotes))
				ptr = expand_substr_ds(env, buf, ptr);
		}
		else
		{
			if (*ptr == '\'' || *ptr == '\"')
				change_quote_modus(&quotes, *ptr);
			add_char_to_buf(buf, *ptr);
			ptr++;
		}
		if (buf->buf == NULL)
			return ;
	}
}
