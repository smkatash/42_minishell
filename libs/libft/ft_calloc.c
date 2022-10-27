/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:29:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/02 17:29:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	char	*ptr;

	ptr = malloc(sizeof(char) * size * count);
	if (ptr == NULL)
		return (NULL);
	bytes = sizeof(char) * size * count;
	while (bytes)
	{
		ptr[bytes - 1] = '\0';
		bytes --;
	}
	return ((void *)ptr);
}
