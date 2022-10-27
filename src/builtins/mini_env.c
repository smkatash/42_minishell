/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:29:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:36:47 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree_mini_env(t_tree_node *branch)
{
	if (branch == NULL)
		return ;
	print_tree_mini_env(branch->left);
	if (branch->value != NULL && branch->for_export)
	{
		ft_putstr_fd(branch->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(branch->value, 1);
		write(1, "\n", 1);
	}
	print_tree_mini_env(branch->right);
}

void	mini_env(t_env *env)
{
	print_tree_mini_env(env->tree);
}
