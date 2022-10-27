/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:25:10 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/27 23:05:36 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_builtins_int(char *builtin, char *argument, int flag)
{
	error_builtins(builtin, argument, flag);
	return (-1);
}

char	*path_error(char *s, int flag)
{
	if (flag == ENOENT)
		flag = EXIT_CMD_NOT_FOUND;
	print_error(s, NULL, NULL, flag);
	error_set_global_exit_status(flag);
	return (NULL);
}

bool	error_builtins_bool(char *builtin, char *argument, int flag, bool ret)
{
	error_builtins(builtin, argument, flag);
	return (ret);
}
