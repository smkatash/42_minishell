/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:31:32 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/29 21:18:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * shifts bytes in buffer to the left whenever it finds a nul byte, so that
 * buf becomes one nul terminated string again.
 */
static void	join_strings(t_char_buf *buf)
{
	int		i;
	char	*src_ptr;
	char	*dst_ptr;

	i = 0;
	src_ptr = buf->buf;
	dst_ptr = buf->buf;
	while (i < buf->size)
	{
		while (*src_ptr)
		{
			*dst_ptr = *src_ptr;
			dst_ptr++;
			src_ptr++;
			i++;
		}
		src_ptr++;
		i++;
	}
	*dst_ptr = '\0';
}

/* when a quote is encountered, calls change_quote_modus to check if quote is 
 * beginning or end of quotation and change quotes variable accordingly. If
 * the modus of quotes was changed, the quote is replaced by a nul byte.
 */
void	exp_remove_quotes(t_char_buf *buf)
{
	int		quotes;
	char	*ptr;

	quotes = NO_QUOTES;
	ptr = buf->buf;
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '\"')
		{
			if (change_quote_modus(&quotes, *ptr))
				*ptr = '\0';
		}
		ptr++;
	}
	join_strings(buf);
}

char	*cmd_rm_quotes(char *s)
{
	t_char_buf	buf;
	char		*ret;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (NULL);
	add_str_to_buf(&buf, s);
	exp_remove_quotes(&buf);
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	free(s);
	return (ret);
}
