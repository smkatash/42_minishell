/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:02:28 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/28 19:01:28 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main part of execution where commands are divided into 
separate functions
- while looping over each node, checks each node type and calls 
relevant functions
- if N_CMD with T_STRING tokens -> goes to simple command/ 
builtin execution
- if the  N_PIPE -> to pipe function
- if N_AND && N_OR -> and_or function
- after execution, the current node is freed ... loop continues 
if there are more nodes
- if forks flag exists -> closes fd_read that was launched during 
the execution.
- At each step -> STATUS is saved to keep track on the process 
EXIT status.
*/
static void	execute_commands_helper(t_ast *node)
{
	if (node)
	{
		if (node->cmds)
			free_cmd_defs(&node->cmds);
		free(node);
	}
}

int	execute_commands(t_exec *exec_cmds, t_minishell *minishell)
{
	int		status;
	t_ast	*node;

	status = 0;
	while (ft_lstsize(*exec_cmds->cmds_list) > 0 && \
		exec_cmds->cmds_list && status == 0)
	{
		node = (t_ast *)lst_get_content(exec_cmds->cmds_list);
		if (node == NULL)
			break ;
		if (node->type == N_CMD && minishell)
			execute_cmds_and_builtins(exec_cmds, &node, minishell);
		else if (node->type == N_PIPE)
			status = execute_pipe(exec_cmds);
		else if (node->type == N_AND || node->type == N_OR)
			execute_and_or_cmd(exec_cmds, node);
		execute_commands_helper(node);
	}
	if (exec_cmds->forks)
		close(exec_cmds->pipe_fd[0]);
	return (status);
}

/* initialization of exec structure and passing list 
of nodes for actual execution
- dup stdin into free fd and dup2 back to stdin in the end of execution
- if list of nodes is 1 -> single builtin is called
- if more nodes, execution of commands verify node type and call
functios according to operator 
- if something goes wrong, lists are free and status 1 is returned 
-> SET GLOBAL STATUS*/
static void	update_exit_status(int status)
{
	if (!WIFSIGNALED(status))
		g_global_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global_exit_status = WTERMSIG(status) + 128;
}

int	start_execution(t_list **nodes, t_minishell *minishell)
{
	int		status;
	int		fd_temp;
	int		total_cmds;
	t_exec	exec_cmds;

	status = 0;
	fd_temp = dup(0);
	init_exec_struct(&exec_cmds, nodes);
	total_cmds = ft_lstsize(*nodes);
	if (total_cmds == 1 && single_builtin(&exec_cmds, minishell))
		return (1);
	status = execute_commands(&exec_cmds, minishell);
	if (status && ft_lstsize(*nodes))
		free_ast_node(nodes);
	if (exec_cmds.forks && (!exec_cmds.builtin || total_cmds > 1))
	{
		while (wait(NULL) > 0);
		update_exit_status(status);
	}
	dup2(fd_temp, 0);
	close(fd_temp);
	if (exec_cmds.fd_out > 1)
		close(exec_cmds.fd_out);
	signal_print(status);
	return (status);
}

/* main execution function */
/*no need to catch status in the if statement, once content of
if statement is true, status is 0, else 1*/
int	main_executor(char *readline, t_minishell *minishell)
{
	int		status;
	t_list	*nodes;
	t_ast	*tree;

	status = 0;
	nodes = NULL;
	tree = ast_builder(readline, minishell->table);
	if (tree)
	{
		get_tree(&nodes, tree, 0);
		status = expander(nodes, minishell->env);
		start_execution(&nodes, minishell);
	}
	else
		status = 1;
	return (status);
}
