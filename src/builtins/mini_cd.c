/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:39:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:36:35 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cd_update_env(t_env *env, char *oldpwd, char *newpwd, short valdup)
{
	int	upd_oldpwd;
	int	upd_newpwd;

	upd_oldpwd = update_env(env, "OLDPWD", oldpwd, EXPORT | KEY_DUP);
	upd_newpwd = update_env(env, "PWD", newpwd, EXPORT | KEY_DUP | valdup);
	if (upd_oldpwd)
	{
		ft_putstr_fd(WARNING_OLDPWD, 2);
		g_global_exit_status = ENOMEM;
	}
	if (newpwd == NULL || upd_newpwd == -1)
	{
		ft_putstr_fd(WARNING_PWD, 2);
		g_global_exit_status = ENOMEM;
	}
}

int	check_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (0);
		return (error_builtins_int("cd", path, EACCESS));
	}
	return (error_builtins_int("cd", path, ENOENT));
}

void	go_home(t_env *env, char *oldpwd)
{
	char	*home;

	home = find_value(env, "HOME");
	if (home == NULL)
		return (error_builtins("cd", NULL, ENOENT));
	if (check_access(home))
		return ;
	if (chdir(home) == -1)
		return (error_builtins("cd", NULL, EXIT_ERROR_DEFAULT));
	mini_cd_update_env(env, oldpwd, home, VAL_DUP);
}

void	mini_cd(int argc, char **argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (error_builtins("cd", NULL, EXIT_ERROR_DEFAULT));
	if (argc == 1)
		return (go_home(env, oldpwd));
	if (check_access(argv[1]))
		return ;
	if (chdir(argv[1]) == -1)
		return (error_builtins("cd", NULL, EXIT_ERROR_DEFAULT));
	newpwd = getcwd(NULL, 0);
	mini_cd_update_env(env, oldpwd, newpwd, 0);
}
