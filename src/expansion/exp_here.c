/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:13:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 21:25:53 by hoomen           ###   ########.fr       */
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

char	*expand_here(t_env *env, char *s)
{
	t_char_buf	buf;
	char		*ret;
	char		*t;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (s);
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
		{
			return (s);
		}
	}
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	if (ret != NULL)
		free(s);
	else
		ret = s;
	return (ret);
}