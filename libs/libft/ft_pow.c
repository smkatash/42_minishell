/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:23:37 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/05 21:51:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double base, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (base * ft_pow(base, power - 1));
}
