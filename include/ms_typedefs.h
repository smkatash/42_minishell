/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:23 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/25 15:57:30 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPEDEFS_H
# define MS_TYPEDEFS_H

# include <stdbool.h>
# include "../libs/libft/libft.h"

/* tree structure where key/value pairs of environment are stored */
typedef struct s_tree_node
{
	char				*key;
	char				*value;
	bool				for_export;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

/* env structure stores a pointer to the key and the current working directory
 * also stores a hash table (array of t_env_hash structs) that grows in size when
 * needed. Struct keeps track of how many entries in hash table, how much entries
 * are free and how much entries were deleted.
 */
typedef struct s_env
{
	t_tree_node			*tree;
	int					size;
}						t_env;

enum e_grammar
{
	NT_START = 0,
	NT_AND_OR,
	NT_AND_OR1,
	NT_PIPESPLIT,
	NT_PIPESPLIT1,
	NT_COMMANDSET,
	NT_COMMANDSET1,
	NT_SUBSHELL,
	NT_CMD,
	NT_CMD1,
	NT_CMD2,
	NT_PREFIX,
	NT_PREFIX1,
	NT_SUFFIX,
	NT_SUFFIX1,
	NT_REDIR,
	NT_REDIR1,
	NT_IO_REDIR,
	NT_IO_FILE,
	NT_IO_HERE,
	T_PIPE,
	T_LBRACE,
	T_RBRACE,
	T_AND,
	T_OR,
	T_LESS,
	T_GREAT,
	T_DGREAT,
	T_LESSGREAT,
	T_DLESS,
	T_ASSIGN,
	T_STRING,
	T_EOF,
	T_UNKNOWN
};

enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_REDIR,
	N_AND_OR,
	N_AND,
	N_OR,
	N_ASSIGN,
	N_SUB,
	N_DUMM
};

typedef struct s_cmd_def
{
	t_list	*cmd;
	t_list	*redir;
	t_list	*assign;
}			t_cmd_def;

typedef struct s_exec
{
	char		**curr_cmd;
	t_list		**cmds_list;
	t_cmd_def	*cmd_type;
	int			status;
	int			pipe_fd[2];
	int			pid;
	int			fd_in;
	int			fd_out;
	int			builtin;
	int			pipe;
	int			forks;
}	t_exec;

typedef struct s_ast
{
	int					node_id;
	int					nodes;
	enum e_node_type	type;
	t_cmd_def			*cmds;
	struct s_ast		*child;
	struct s_ast		*prev_sibling;
	struct s_ast		*next_sibling;
}						t_ast;

typedef struct s_minishell
{
	int				line_len;
	char			*line;
	void			(***table)(t_list **, enum e_grammar);
	t_env			*env;
	struct termios	termios_cpy;
}					t_minishell;

#endif
