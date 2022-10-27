/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:28:45 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/27 22:58:26 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_syntax_error(char *token)
{
	char	*error_message;
	char	*temp;

	g_global_exit_status = 258;
	if (token)
	{
		temp = ft_strjoin("syntax error near unexpected token `", token);
		error_message = ft_strjoin(temp, "´");
		free(temp);
		error_shell(error_message, ERROR_UNDEFINED);
		free (error_message);
	}
	else
	{
		error_message = "parse error near`\\n´";
		error_shell(error_message, ERROR_UNDEFINED);
	}
}

int	parsing_lexer_error(void)
{
	g_global_exit_status = 258;
	error_shell("parse error: unbalanced quotes", ERROR_UNDEFINED);
	return (EXIT_ERROR_DEFAULT);
}

void	exec_command_error(char *cmd, int flag)
{
	char	*error_message;

	if (flag == 1)
	{
		error_message = ft_strjoin(cmd, ": is a directory");
		g_global_exit_status = (127 - flag);
	}
	else
	{
		error_message = ft_strjoin(cmd, ": command not found");
		g_global_exit_status = 127;
	}
	error_shell(error_message, g_global_exit_status);
	free(error_message);
}

int	redirect_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(": failed to redirect", 2);
	g_global_exit_status = 1;
	return (EXIT_FAILURE);
}

int	expansion_error(char *error_message, int flag)
{
	if (flag == ERROR_REDIR)
		redirect_error(error_message);
	if (flag == ERROR_CMD)
		simple_command_error(error_message);
	return (1);
}
