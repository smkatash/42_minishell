/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:13:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* duplicates a string using ft_strdup. On succes, returns 0. If malloc fails,
 * returns -1. */
int	ft_strdup_int(char **dup, char *s)
{
	*dup = ft_strdup(s);
	if (*dup == NULL && s != NULL)
		return (-1);
	return (0);
}
