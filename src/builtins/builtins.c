/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/28 17:57:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *s)
{
	if (s == NULL)
		return (false);
	if (ft_strncmp_uplo(s, "echo", 5) && ft_strcmp(s, "cd")
		&& ft_strcmp(s, "pwd") && ft_strcmp(s, "export")
		&& ft_strcmp(s, "unset") && ft_strcmp(s, "env")
		&& ft_strcmp(s, "exit"))
		return (false);
	return (true);
}

void	call_builtin(int argc, char **argv, t_minishell *minishell)
{
	if (argv[0] == NULL)
		return (error_builtins(argv[0], NULL, ERROR_UNDEFINED));
	if (!ft_strcmp(argv[0], "exit"))
	{
		mini_exit(argc, argv, minishell);
		return ;
	}
	g_global_exit_status = 0;
	if (!ft_strcmp(argv[0], "pwd"))
		mini_pwd();
	else if (!ft_strcmp(argv[0], "env"))
		mini_env(minishell->env);
	else if (ft_strncmp_uplo(argv[0], "echo", 5) == 0)
		mini_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(argc, argv, minishell->env);
}

bool	builtin_child_process(t_exec *exec, t_cmd_def *cmd, \
t_minishell *minishell)
{
	char	*cmd_s;
	int		argc;
	char	**argv;

	cmd_s = exec->cmd_type->cmd->content;
	if (!is_builtin(cmd_s))
		return (false);
	argv = list_to_argv(exec->cmd_type->cmd, &argc);
	free_cmd_defs(&cmd);
	duplicate_fd(exec);
	if (argv != NULL)
		call_builtin(argc, argv, minishell);
	else
		error_builtins(cmd_s, NULL, ENOMEM);
	ft_freestrarr(&argv);
	free_minishell(minishell);
	return (true);
}

/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
bool	single_builtin(t_exec *exec, t_minishell *minishell)
{
	t_ast	*node;
	int		argc;
	char	**argv;
	int		fd_cpys[2];
	char	*cmd;

	node = get_ast_node(exec);
	if (node == NULL || node->cmds == NULL || node->cmds->cmd == NULL)
		return (false);
	cmd = node->cmds->cmd->content;
	if (!is_builtin(cmd))
		return (false);
	if (run_redirections_single_builtin(exec, node, fd_cpys, minishell))
		return (true);
	wildcard_expander(&node->cmds->cmd);
	argv = list_to_argv(node->cmds->cmd, &argc);
	free_single_builtin(exec, node);
	if (argv == NULL)
		error_builtins(cmd, NULL, ENOMEM);
	else
		call_builtin(argc, argv, minishell);
	restore_stdin_stdout_builtin(exec, fd_cpys);
	ft_freestrarr(&argv);
	return (true);
}
