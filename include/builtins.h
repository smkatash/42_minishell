/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 19:11:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ms_typedefs.h"

/* builins.c */
// bool	builtin(t_exec *exec_cmds, t_minishell *minishell, bool single_builtin);
bool	single_builtin(t_exec *exec, t_minishell *minishell);
bool	builtin_child_process(t_exec *exec, t_cmd_def *cmd, \
t_minishell *minishell);

/* redirections_builtin.c*/
int		run_redirections_single_builtin(t_exec *exec, t_ast *node, \
int fd_cpys[2], t_minishell *minishell);
void	restore_stdin_stdout_builtin(t_exec *exec, int fd_cpys[2]);

/* builtin_utils.c */
t_ast	*get_ast_node(t_exec *exec);
void	free_single_builtin(char **argv, t_exec *exec, t_ast *node);

/* builtin echo */
void	mini_echo(int argc, char **argv);

/* builtin cd */
void	mini_cd(int argc, char **argv, t_env *env);

/* builtin env */
void	mini_env(t_env *env);

/* builtin mini_unset */
void	mini_unset(int argc, char **argv, t_env *env);

/* builtin mini_pwd */
void	mini_pwd(void);

/* builtin mini_export */
bool	first_char_valid(char c);
void	mini_export(int argc, char **argv, t_env *env);

/* builtin mini_exit */
void	mini_exit(int argc, char **argv, t_minishell *minishell);

# define WARNING_OLDPWD "minishell: unable to update OLDPWD variable\
(System error)"
# define WARNING_PWD "minishell: unable to update PWD variable\
(System error)"

#endif
