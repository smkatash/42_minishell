/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:06:20 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:28 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* returns the address where a new node should be inserted, based on the key
 * of the new node. If the key already exists, it returns the address of the 
 * node which contains the existing key. If the node does not exist, it returns
 * the address of a NULL pointer that should be set to point to the new node.
 */
t_tree_node	**position_in_tree(t_tree_node **tree, char *key)
{
	int	ret;

	if (*tree == NULL)
		return (tree);
	ret = ft_strcmp(key, (*tree)->key);
	if (ret == 0)
		return (tree);
	if (ret < 0)
		return (position_in_tree(&((*tree)->left), key));
	return (position_in_tree(&((*tree)->right), key));
}

/* searches the tree for a given value and returns the node containing that
 * key.
 */
t_tree_node	*get_env_node(t_tree_node **tree, char *key)
{
	t_tree_node	**position;

	position = position_in_tree(tree, key);
	if (position == NULL)
		return (NULL);
	return (*position);
}

/* makes a new node based on a key value pair. Key and value should already be
 * stored dynamically
 */
t_tree_node	*new_node(char *key, char *value, short flags)
{
	t_tree_node	*new;

	new = malloc(sizeof(t_tree_node));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->for_export = flags & EXPORT;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/* adds a new node into the tree
 */
void	add_node(t_tree_node **tree, t_tree_node *new)
{
	*(position_in_tree(tree, new->key)) = new;
}

/* searches the tree for a given key and returns a pointer to the value
 */
char	*find_value(t_env *env, char *key)
{
	t_tree_node	**position;

	position = position_in_tree(&(env->tree), key);
	if (*position == NULL)
		return (NULL);
	return ((*(position_in_tree(&(env->tree), key)))->value);
}
