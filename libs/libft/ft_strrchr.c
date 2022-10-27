/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:07:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/02 16:30:21 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			ptr = (char *) s + i;
		i++;
	}
	if (s[i] == c)
		return ((char *) s + i);
	return (ptr);
}
