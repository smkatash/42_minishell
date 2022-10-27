/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:35:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:48:17 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	calculate_number(const char *str, int i, int sign)
{
	long int	nb;

	nb = 0;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + ((str[i]) - '0');
		if (nb > 2147483647 && sign == 1)
			return (-1);
		if (nb > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (nb * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = (int) calculate_number(str, i, sign);
	return (nb);
}
