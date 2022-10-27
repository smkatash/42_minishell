/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:33:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:40:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_strcmp_strnstr(char *haystack, char *needle, size_t len)
{
	if (!*needle)
		return (1);
	if (!*haystack)
		return (0);
	if (!len)
		return (0);
	if (*haystack != *needle)
		return (0);
	else
		return (ft_strcmp_strnstr(haystack + 1, needle + 1, len - 1));
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*needle)
		return ((char *) haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
			if (ft_strcmp_strnstr((char *)haystack + i, \
			(char *)needle, len - i))
				return ((char *)haystack + i);
		i ++;
	}
	return (0);
}
