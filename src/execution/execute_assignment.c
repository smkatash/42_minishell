/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:57:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 21:42:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_assignment(t_list *assign_lst, t_minishell *shell)
{
	int			status;

	status = 0;
	if (!assign_lst)
		return (status);
	while (assign_lst && status == 0)
	{
		status = update_env_string(shell->env, assign_lst->content, \
			ASSIGN | NO_EXPORT);
		assign_lst = assign_lst->next;
	}
	return (status);
}
