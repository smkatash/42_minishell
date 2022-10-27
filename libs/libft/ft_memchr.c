/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:51:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/02 17:30:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	cc;
	size_t	i;

	cc = (char) c;
	i = 0;
	while (i < n)
	{
		if (*((char *)s + i) == cc)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
