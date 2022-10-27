/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/27 01:18:00 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ms_typedefs.h"

int	g_global_exit_status;

enum e_type
{
	type_file,
	type_dir
};

typedef struct s_expansion
{
	char		*file;
	enum e_type	type;
}				t_expansion;

// Main xecution
int			main_executor(char *readline, t_minishell *minishell);
int			start_execution(t_list **nodes, t_minishell *minishell);
int			execute_commands(t_exec *exec_cmds, t_minishell *minishell);
void		execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, \
			t_minishell *minishell);
void		get_tree(t_list **nodes, t_ast *tree, int node_id);
void		init_exec_struct(t_exec *exec, t_list **cmds_list);
int			get_redirect_file(t_list **redir_list, char **file, int here_doc);
char		*remove_quotes(char *str);

// && ||
int			execute_and_or_cmd(t_exec *exec, t_ast *node);

// Assignment
int			execute_assignment(t_list *assign_lst, t_minishell *shell);

// Heredoc redirection
void		child_process_heredoc(char *delim, int *fd, t_exec *exec, \
			t_minishell *shell);
int			execute_heredoc(char *delim, t_exec *exec, t_minishell *shell);

// Execute redirections
int			execute_redirection(t_exec	*exec, t_minishell *minishell);
void		update_redir(t_exec *exec, t_list **redir, int *here_doc);
int			redirect_here_doc(char *file, int flag, t_exec *exec, \
			t_minishell *minishell);

// Execute commands
int			execute_cmd_block(t_exec *exec_cmds, t_ast *node, \
			t_minishell *minishell);
int			execute_pipe(t_exec *exec);
void		duplicate_fd(t_exec *exec);
int			run_cmd_child(t_exec *exec, t_cmd_def *cmd, \
			t_minishell *minishell);
int			fork_process(t_exec *exec_cmds, t_cmd_def *cmds, \
			t_minishell *minishell);

// Wildcard bonus
int			wildcard_expander(t_list **cmds);
void		filename_expansion(t_list **redir_list);
void		merge_to_list(t_list **curr_lst, t_list *new, \
			t_list *prev, t_list **lst);
t_list		*expand_star(char *str);
void		get_redirlst(DIR *temp_dir, char *dir, t_list *path, t_list **lst);
size_t		no_star_part(char *text);
char		*ft_strstr(char *haystack, char *needle);
int			file_list_comparison(char *search, char *files);
int			file_cmp(char *search, char	*files);
t_list		*get_path_for_expansion(char *str);
char		*get_path(char *dir_path, char *path);
int			init_root_dir(t_list **list);
int			init_path_lst(char **path, t_list **list);
void		free_path_split(char **split);
void		push_to_redirlst(t_list *path, t_list **lst, char *dir);
void		get_full_redirlst(DIR *temp_dir, char *dir, t_list *path, \
			t_list **lst);
void		get_expand_direct(t_list **lst, t_list *path);
void		add_redirlst(char *curr_dir, t_list *dir_list, t_list **lst);
char		*get_file(t_list *lst);
t_expansion	*init_file(char	*file, enum e_type type);
void		update_type_file(t_list	*lst);
int			dir_type(unsigned char type);
int			dir_type_checker(enum e_type d_type, int type);

// Find path
char		*find_path(char *command, t_env *env);

// Convert t_list with cmd + argument into argv for execve
char		**list_to_argv(t_list *cmd, int *argc);

#endif
