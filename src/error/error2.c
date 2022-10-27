/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:24:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/26 19:07:48 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(": argument is too long", 2);
	g_global_exit_status = EXIT_CANNOT_EXECUTE;
}

int	error_shell(char *error_message, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (flag == ERROR_UNDEFINED)
		ft_putendl_fd(error_message, 2);
	else if (flag == ERROR_PERROR)
		perror(error_message);
	g_global_exit_status = EXIT_FAILURE;
	return (1);
}

void	error_set_global_exit_status(int flag)
{
	if (flag == ENOENT)
		g_global_exit_status = EXIT_CMD_NOT_FOUND;
	else if (flag == EACCESS)
		g_global_exit_status = EXIT_CANNOT_EXECUTE;
	else if (flag == ENOMEM)
		g_global_exit_status = EXIT_OUT_OF_MEMORY;
	else
		g_global_exit_status = EXIT_ERROR_DEFAULT;
}

void	error_builtins(char *builtin, char *argument, int flag)
{
	if (flag == ERROR_PERROR && argument != NULL)
		print_error(builtin, NULL, argument, 0);
	else if (flag == ERROR_PERROR)
		print_error(NULL, NULL, builtin, 0);
	else
		print_error(builtin, argument, NULL, flag);
	if (flag == ENOMEM)
		g_global_exit_status = EXIT_OUT_OF_MEMORY;
	else
		g_global_exit_status = EXIT_ERROR_DEFAULT;
}
