/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:00:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/28 17:49:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_mini_us(char *s)
{
	size_t	i;

	if (s[0] == '\0')
		return (false);
	i = 0;
	while (s[i])
	{
		if (i == (size_t) - 1)
			return (false);
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	mini_unset(int argc, char **argv, t_env *env)
{
	int		i;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i] != NULL)
	{
		if (!ft_strcmp("_", argv[i]))
		{
			i++;
			continue ;
		}
		if (is_valid_mini_us(argv[i]))
			del_tree_node(&(env->tree), NULL, argv[i], 0);
		else
		{
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(argv[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
			g_global_exit_status = 1;
		}
		i++;
	}
}
