/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:23:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/27 17:45:45 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_env *env, char *key, char *value, short flags)
{
	t_tree_node	**pos;
	char		*val_dup;

	pos = position_in_tree(&(env->tree), key);
	if (pos == NULL || *pos == NULL)
		return (add_key_value_to_env(env, key, value, flags));
	if ((value != NULL && ((*pos)->value == NULL
				|| ft_strcmp((*pos)->value, value))) || flags & VAL_OVERW)
	{
		if (flags & VAL_DUP)
		{
			if (ft_strdup_int(&val_dup, value) == -1)
				return (error_builtins_int(key, NULL, ENOMEM));
		}
		else
			val_dup = value;
		free((*pos)->value);
		(*pos)->value = val_dup;
	}
	if (!(flags & ASSIGN))
		(*pos)->for_export = flags & EXPORT;
	return (0);
}

int	update_env_node(t_tree_node *node, char *value, short flags)
{
	char	*val_dup;

	if (value == NULL && flags ^ VAL_OVERW)
		return (1);
	if (flags & VAL_DUP)
	{
		if (ft_strdup_int(&val_dup, value) == -1)
			return (-1);
	}
	else
		val_dup = value;
	free(node->value);
	node->value = val_dup;
	if (!(flags & ASSIGN))
		node->for_export = flags & EXPORT;
	return (0);
}

int	update_env_string(t_env *env, char *s, short flags)
{
	char	*value;
	char	*key;
	int		ret;

	key = ft_strdup(s);
	if (key == NULL)
		return (-1);
	value = manipulate_ptrs(key);
	ret = update_env(env, key, value, flags | VAL_DUP | KEY_DUP);
	free(key);
	return (ret);
}
