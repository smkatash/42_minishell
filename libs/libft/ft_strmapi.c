/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:59:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/02 17:38:35 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	s2 = ft_calloc(len + 1, sizeof(char));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s2[i] = (*f)(i, s[i]);
		i++;
	}
	return (s2);
}
