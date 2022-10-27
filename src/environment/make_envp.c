/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:29:15 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:35 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_strarr_int(char ***strarr, int ret)
{
	int		i;
	char	**strarr1;

	strarr1 = *strarr;
	i = 0;
	while (strarr1[i] != NULL)
	{
		free(strarr1[i]);
		i++;
	}
	free(strarr1);
	*strarr = NULL;
	return (ret);
}

int	triple_strjoin_int(char **triple, char *s1, char *s2, char *s3)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (join == NULL)
		return (-1);
	*triple = ft_strjoin(join, s3);
	free(join);
	if (*triple == NULL)
		return (-1);
	return (0);
}

int	tree_to_strarr(t_tree_node *branch, char ***envp, int *i)
{
	if (branch == NULL)
		return (0);
	if (tree_to_strarr(branch->left, envp, i) == -1)
		return (-1);
	if (branch->for_export)
	{
		if (branch->value == NULL)
		{
			if (ft_strdup_int((*envp) + *i, branch->key))
				return (free_strarr_int(envp, -1));
		}
		else
		{
			if (triple_strjoin_int((*envp) + *i, branch->key, "=",
					branch->value) == -1)
				return (free_strarr_int(envp, -1));
		}
		(*i)++;
	}
	if (tree_to_strarr(branch->right, envp, i) == -1)
		return (-1);
	return (0);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = ft_calloc((env->size + 1), sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	if (tree_to_strarr(env->tree, &envp, &i) == -1)
		return (NULL);
	return (envp);
}
