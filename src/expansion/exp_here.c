/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:13:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/29 19:09:14 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_rm_quotes(char *delim)
{
	t_char_buf	buf;
	int			i;
	int			quotes;
	char		*ret;

	init_char_buf(&buf);
	quotes = NO_QUOTES;
	i = -1;
	while (delim[++i])
	{
		if (delim[i] == '\'' || delim[i] == '\"')
		{
			if (!change_quote_modus(&quotes, delim[i]))
				add_char_to_buf(&buf, delim[i]);
		}
		else
			add_char_to_buf(&buf, delim[i]);
		if (buf.buf == NULL)
			return (delim);
	}
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	free(delim);
	return (ret);
}

static char	*expansion_error_here(char *s, t_char_buf buf)
{
	ft_putstr_fd("minishell: unable to expand (out of memory)\n", 2);
	free(s);
	free(buf.buf);
	return (NULL);
}

static char	*init_char_buf_check(t_char_buf *buf, char *s)
{
	if (s == NULL)
		return (NULL);
	init_char_buf(buf);
	if (buf->buf == NULL)
		return (expansion_error_here(s, *buf));
	else
		return (buf->buf);
}

char	*expand_here(t_env *env, char *s)
{
	t_char_buf	buf;
	char		*ret;
	char		*t;

	if (init_char_buf_check(&buf, s) == NULL)
		return (NULL);
	t = s;
	while (*t)
	{
		if (*t == '$' && !is_end_of_key(*(t + 1)))
			t = expand_substr_ds(env, &buf, t);
		else
		{
			add_char_to_buf(&buf, *t);
			t++;
		}
		if (buf.buf == NULL)
			return (expansion_error_here(s, buf));
	}
	ret = ft_strdup(buf.buf);
	if (ret == NULL)
		return (expansion_error_here(s, buf));
	free(buf.buf);
	free(s);
	return (ret);
}
