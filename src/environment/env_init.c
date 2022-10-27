/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:59:00 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:08:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* creates a minimal envorionment if minishell was not give an 
 * environment (e.g. by running minishell with env -i)
 * We assume that minishell was called from the current working
 * directory and set _= accordingly. It is beyond the scope of
 * this project to set it fully correctly.
 */
void	startup_without_environment(t_env *env, t_minishell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit_minishell(ERROR_UNDEFINED, INIT, "getcwd", minishell);
	if (add_key_value_to_env(env, "PWD", cwd, EXPORT | VAL_DUP | KEY_DUP) == -1)
		exit_minishell(ENOMEM, INIT, NULL, minishell);
	if (add_string_to_env(env, "SHLVL=1", EXPORT) == -1)
		exit_minishell(ENOMEM, INIT, NULL, minishell);
	if (add_key_value_to_env(env, "_=", cwd, EXPORT | KEY_DUP) == -1)
		exit_minishell(ENOMEM, INIT, NULL, minishell);
}

/* increases the SHLVL (shell level) variable by one. If not specified or 0
 * or invalid, sets SHLVL to 1.
 */
int	update_shlvl(t_env *env, t_minishell *minishell)
{
	t_tree_node	*node;
	int			nbr;
	char		*value;

	node = get_env_node(&(env->tree), "SHLVL");
	if (node == NULL)
		return (add_key_value_to_env(env, "SHLVL", "1", EXPORT | VAL_DUP \
				| KEY_DUP));
	nbr = ft_atoi(node->value);
	if (nbr < 1)
		return (update_env_node(node, "1", EXPORT | VAL_DUP));
	if (nbr == 999)
	{
		if ((update_env_node(node, "0", EXPORT | VAL_DUP) == -1))
			return (-1);
		ft_putstr_fd(WARNING_TOO_MANY_SHLVLS, 2);
		return (1);
	}
	value = ft_itoa(nbr + 1);
	if (value == NULL)
		exit_minishell(ENOMEM, INIT, NULL, minishell);
	return (update_env_node(node, value, EXPORT));
}

void	init_env(t_env *env, char **envp, t_minishell *minishell)
{
	int	i;

	if (env == NULL)
		return ;
	if (envp == NULL || envp[0] == NULL)
	{
		startup_without_environment(env, minishell);
		return ;
	}
	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			continue ;
		if (add_string_to_env(env, envp[i], EXPORT) == -1)
			exit_minishell(ENOMEM, INIT, NULL, minishell);
	}
	if (update_shlvl(env, minishell) == -1)
		exit_minishell(ENOMEM, INIT, NULL, minishell);
}
