/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 19:12:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "ms_typedefs.h"

/* flags for the functions that add new key/value pairs to the environment. 
 * NO_EXPORT = variable should not be marked for export
 * EXPORT = variable should be marked for export
 * KEY_DUP = key is a pointer to a string that should be duplicated (malloced)
 * VAL_DUP = id for value
 * VAL_OVERW = when updating an existing key, overwrite the existing value
 */
# define NO_EXPORT 0
# define EXPORT 0b1
# define KEY_DUP 0b10
# define VAL_DUP 0b100
# define VAL_OVERW 0b1000
# define ASSIGN 0b10000

# define WARNING_TOO_MANY_SHLVLS "Minishell: Warning: level of shells (1000) \
too high, resetting to 0"

/* tree2.c */
t_tree_node	**position_in_tree(t_tree_node **tree, char *key);
t_tree_node	*get_env_node(t_tree_node **tree, char *key);
t_tree_node	*new_node(char *key, char *value, short flags);
void		add_node(t_tree_node **tree, t_tree_node *new_node);
char		*find_value(t_env *env, char *key);

/* env_init.c */
void		init_env(t_env *env, char **envp, t_minishell *minishell);

/* add_to_env.c */
int			add_to_tree(t_env *env, char *key, char *value, short flags);
int			add_key_value_to_env(t_env *env, char *key, char *value, \
short flags);
char		*manipulate_ptrs(char *s);
int			add_string_to_env(t_env *env, char *s, short flags);

/* update_env.c */
void		update_node(t_tree_node *node, char *value, short flags);
int			update_env(t_env *env, char *key, char *value, short flags);
int			update_env_node(t_tree_node *node, char *value, short flags);
int			update_env_string(t_env *env, char *value, short flags);

/* env_utils.c */
int			ft_strdup_int(char **dup, char *s);

/* make_envp.c */
int			free_strarr(char ***strarr, int ret);
int			triple_strjoin_int(char **triple, char *s1, char *s2, char *s3);
int			tree_to_strarr(t_tree_node *branch, char ***envp, int *i);
char		**make_envp(t_env *env);

/* print_tree.c */
void		print_tree(t_tree_node *node, int fd);

/* env_free.c */
void		clear_env(t_env **env);
int			del_key_value(char *key, char *value, short flags, int ret);
int			del_tree_node(t_tree_node **tree, t_tree_node **node, char *key, \
int ret);
void		free_tree(t_tree_node **tree);

#endif
