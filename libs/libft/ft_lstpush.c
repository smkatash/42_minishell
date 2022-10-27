/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:48:58 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/15 12:49:33 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **lst, void *data)
{
	t_list	*new;

	new = ft_lstnew(data);
	ft_lstadd_front(lst, new);
}
