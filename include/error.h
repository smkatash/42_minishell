/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:18:10 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/25 15:57:47 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "../libs/libft/libft.h"
# include <stdio.h>

# define EXIT_MINISHELL_SUCCESS 0
# define EXIT_ERROR_DEFAULT 1 
# define EXIT_CANNOT_EXECUTE 126 /*"Command invoked cannot execute"*/
# define EXIT_CMD_NOT_FOUND 127 /*"Command not found"*/
# define EXIT__ARG_TO_EXIT 128 /*"Invalid argument to exit"*/
# define EXIT_ERROR_SIGNAL_N 128 /*"Fatal error signal “n”"*/
# define EXIT_ERROR_CNRTL_C 130 /*"Script terminated by Control-C"*/
# define EXIT_EXIT_OUT_OF_RANGE 255 /*"Exit status out of range"*/
# define EXIT_OUT_OF_MEMORY 137

# define ENOENT 2 /*"No such file or directory"*/
# define ECHILD 10 /*"No child processes"*/
# define ENOMEM 12 /*"Out of memory"*/
# define EACCESS 13 /*"Permission denied"*/
# define ENOTDIR 20 /*"Not a directory"*/
# define ENODATA 61 /*"No data available"*/
# define ERROR_UNDEFINED 4
# define ERROR_PERROR 5
# define ERROR_REDIR 6
# define ERROR_CMD 7
# define SYS_ERR 8
/* phase of the program where exit_minishell is called */
# define INIT 0

int		error_shell(char *error_message, int flag);
void	exec_command_error(char *cmd, int flag);
int		parsing_lexer_error(void);
void	parsing_syntax_error(char *token);
int		expansion_error(char *error_message, int flag);
void	simple_command_error(char *error_message);
int		redirect_error(char *error_message);
void	error_builtins(char *builtin, char *argument, int flag);
char	*path_error(char *s, int flag);
int		error_builtins_int(char *builtin, char *argument, int flag);
void	error_set_global_exit_status(int flag);
void	print_error(char *arg1, char *arg2, char *arg_perror, int flag);
/* exit minishell in case an error occurs (during initialization) */
void	exit_minishell(int flag, int PHASE, char *error, \
		t_minishell *minishell);

#endif
