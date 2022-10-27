/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:24:22 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:07:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* called when there is not enough space in the buffer to add the HOME string.
 * A new buffer is created, the size of the old buffer + enough BUFSIZE units to
 * make the HOME string fit (usually one BUFSIZE). Tilde is copied to the
 * beginning of the new buf, the old buf is copied thereafter. Old buf is freed.
 */
void	tilde_to_new_buf(char *tilde, t_char_buf *buf, int tilde_len)
{
	char	*new_buf;
	int		add;
	int		oldbufsize;

	add = ((tilde_len / BUFSIZE) + 1) * BUFSIZE;
	oldbufsize = ((buf->size / BUFSIZE) + 1) * BUFSIZE;
	new_buf = malloc((oldbufsize + add) * sizeof(char));
	if (new_buf == NULL)
	{
		g_global_exit_status = ENOMEM;
		ft_putstr_fd("minishell: failed to expand tilde (out of memory)\n", 2);
		free(buf->buf);
		buf->buf = NULL;
		return ;
	}
	ft_memmove(new_buf, tilde, tilde_len);
	ft_memmove(new_buf + tilde_len, buf->buf + 1, buf->size);
	buf->size += tilde_len - 1;
	buf->free = sizeof(new_buf) - buf->size - 1;
	ft_memset(new_buf + buf->size, 0, buf->free + 1);
	free(buf->buf);
	buf->buf = new_buf;
}

/* tilde is only expanded if it is at the beginning of a token and if it's
 * immediately followd by a slash. If there is enough space in the buffer, the
 * existing chars are moved to the right (with memmove) so that the HOME string
 * fits in front. If not enough space is availablle in the buffer,
 * tilde_to_new_buf is called to extend te buffer
 **/
void	expand_tilde(t_env *env, t_char_buf *buf)
{
	char	*tilde;
	int		tilde_len;

	if (buf->buf[0] != '~')
		return ;
	if (buf->buf[1] != '/' && buf->buf[1] != '\0')
		return ;
	tilde = find_value(env, "HOME");
	if (tilde == NULL)
		return ;
	tilde_len = (int) ft_strlen(tilde);
	if (tilde_len + buf->size > buf->free)
		return (tilde_to_new_buf(tilde, buf, tilde_len));
	ft_memmove(buf->buf + tilde_len, buf->buf + 1, buf->size - 1);
	ft_memmove(buf->buf, tilde, tilde_len);
	buf->size += tilde_len - 1;
	buf->free -= tilde_len + 1;
}
