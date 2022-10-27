/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:33:10 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:12 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* deletes a given node and frees all memory associated with it.
 * Reinserts sub trees starting at the deleted node back into the tree.
 * Takes as a parameter the node to be deleted. If node = NULL, searches
 * for the node to be deleted based on the key parameter Returns 0 upon 
 * success, 1 if the node was not found.
 */
int	del_tree_node(t_tree_node **tree, t_tree_node **node, char *key, int ret)
{
	t_tree_node	*left;
	t_tree_node	*right;
	t_tree_node	*del;

	if (node == NULL)
		node = position_in_tree(tree, key);
	del = *node;
	if (del == NULL)
		return (0);
	left = del->left;
	right = del->right;
	free(del->key);
	del->key = NULL;
	free(del->value);
	del->value = NULL;
	free(del);
	*node = NULL;
	if (left != NULL)
		*(position_in_tree(tree, left->key)) = left;
	if (right != NULL)
		*(position_in_tree(tree, right->key)) = right;
	return (ret);
}

/* frees whole tree and sets the pointer to the tree to NULL
 */
void	free_tree(t_tree_node **tree)
{
	t_tree_node	*node;

	node = *tree;
	if (node == NULL)
		return ;
	free_tree(&(node->left));
	free_tree(&(node->right));
	free(node->key);
	free(node->value);
	free(node);
	*tree = NULL;
}

int	del_key_value(char *key, char *value, short flags, int ret)
{
	if (key != NULL && (flags & KEY_DUP))
		free(key);
	if (value != NULL && (flags & VAL_DUP))
		free(value);
	return (ret);
}

void	clear_env(t_env **env_dir)
{
	t_env	*env;

	if (*env_dir == NULL)
		return ;
	env = *env_dir;
	free_tree(&(env->tree));
	*env_dir = NULL;
	free(env);
	*env_dir = NULL;
}
