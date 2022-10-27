/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:40:12 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/02 17:42:06 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sublen;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) + 1)
		return (ft_calloc(1, 1));
	sublen = ft_strlen(s) - start;
	if (sublen > len)
		sublen = len;
	substr = malloc(sizeof(char) * (sublen + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
