/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:34:28 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:03:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** checks if a file exists, in which case it sets file_exists (passed by
 * reference) to true and the checks if access rights are ok for execution. If
 * so, returns 0. If no file exists, or there are no permissions, -1 is
 * returned.
 */
int	my_access(char *command, bool *file_exists)
{
	if (access(command, F_OK) == 0)
	{
		*file_exists = true;
		if (access(command, X_OK) == 0)
			return (0);
	}
	return (-1);
}

/* calls find_value to get a pointer to the value associated with PATH variable.
 * If PATH is unset, return NULL and sets global exit status to ENOENT. If
 * malloc fails in the splitting of the path value, also returns NULL and sets
 * global exit status to ENOMEM. If all goes correctly, returns an array of
 * paths.
 */
char	**extract_all_paths(t_env *env, char *command)
{
	char	*paths_value;
	char	**paths;

	paths_value = find_value(env, "PATH");
	if (paths_value == NULL)
		return ((char **) path_error(command, ENOENT));
	paths = ft_split(paths_value, ':');
	if (paths == NULL)
		return ((char **) path_error(command, ENOMEM));
	return (paths);
}

/* goes through the array of all paths, for every one, first adds a slash, then
 * adds the command. If my_access returns 0, returns the created path. If not,
 * tries the next path. Keeps track of whether the file exists, in order to set
 * global access status correctly (to EACCES or ENOENT) and return NULL if no
 * file is found or if for all files found the access is prohibited.
 */
char	*assemble_path(char **all_paths, char *command)
{
	int		i;
	char	*with_slash;
	char	*path;
	bool	file_exists;

	i = 0;
	file_exists = false;
	while (all_paths[i] != NULL)
	{
		with_slash = ft_strjoin(all_paths[i], "/");
		if (with_slash == NULL)
			return (path_error(command, ENOMEM));
		path = ft_strjoin(with_slash, command);
		free(with_slash);
		if (path == NULL)
			return (path_error(command, ENOMEM));
		if (my_access(path, &file_exists) == 0)
			return (path);
		free(path);
		i++;
	}
	if (file_exists)
		return (path_error(command, EACCESS));
	return (path_error(command, ENOENT));
}	

/* function is called in case command contains a forward slash. Checks if the
 * path exists and if permissions are given. If so, strdups command and returns
 * it. If not, or if malloc fails (strdup return NULL), NULL is returned and
 * global exit status is set accordingly
 */
char	*check_full_path(char *command)
{
	bool	file_exists;
	char	*path;

	file_exists = false;
	if (my_access(command, &file_exists) == 0)
	{
		path = ft_strdup(command);
		if (path == NULL)
			return (path_error(command, ENOMEM));
		return (path);
	}
	if (file_exists)
		return (path_error(command, EACCESS));
	return (path_error(command, ENOENT));
}

/* if command contains a forward slash, it means that it is a full path.
 * check_ful_path is called to strdup command, check access and return the path
 * or set global acces status if there is no such file, if access is denied or
 * if strdup failed. If command does not contain a slash, all_paths are
 * extracted from the env tree, the path is assembled and the access is checked.
 * Function returns the full path when found, returns NULL when not found or
 * when no access or when malloc failed at some point. In all those cases,
 * g_global_exit_status is set accordingly.
 * */
char	*find_path(char *command, t_env *env)
{
	char	**all_paths;
	char	*path;

	if (ft_strchr(command, '/'))
		return (check_full_path(command));
	all_paths = extract_all_paths(env, command);
	if (all_paths == NULL)
		return (NULL);
	path = assemble_path(all_paths, command);
	ft_freestrarr(&all_paths);
	return (path);
}
