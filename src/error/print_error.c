/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:48:12 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:02 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg_suffix(char *arg, char *suffix)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(suffix, 2);
}

void	print_flag2(int flag)
{
	char	*message;

	if (flag == EXIT_CANNOT_EXECUTE)
		message = "Command invoked cannot execute";
	else if (flag == EXIT_CMD_NOT_FOUND)
		message = "Command not found";
	else if (flag == EXIT__ARG_TO_EXIT)
		message = "Invalid argument to exit";
	else if (flag == EXIT_ERROR_SIGNAL_N)
		message = "Fatal error signal";
	else if (flag == EXIT_ERROR_CNRTL_C)
		message = "Script terminated by Control-C";
	else if (flag == EXIT_EXIT_OUT_OF_RANGE)
		message = "Exit status out of range";
	else
		message = "Undefined error";
	print_arg_suffix(message, "\n");
}

void	print_flag(int flag)
{
	char	*message;

	if (flag == ENOENT)
		message = "No such file or directory";
	else if (flag == ECHILD)
		message = "No child processes";
	else if (flag == ENOMEM)
		message = "Out of memory";
	else if (flag == EACCESS)
		message = "Permission denied";
	else if (flag == ENOTDIR)
		message = "Not a directory";
	else if (flag == ENODATA)
		message = "No data available";
	else
		return (print_flag2(flag));
	print_arg_suffix(message, "\n");
}

void	print_error(char *arg1, char *arg2, char *arg_perror, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg1 != NULL)
		print_arg_suffix(arg1, ": ");
	if (arg2 != NULL)
		print_arg_suffix(arg2, ": ");
	if (arg_perror)
		perror(arg_perror);
	else if (flag != -1)
		print_flag(flag);
}
