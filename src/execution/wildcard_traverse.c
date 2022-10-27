/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_traverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:42:19 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/26 21:43:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirlst(char *curr_dir, t_list *dir_list, t_list **lst)
{
	DIR	*temp_dir;

	if (curr_dir)
		temp_dir = opendir(curr_dir);
	else
		temp_dir = opendir(".");
	if (!temp_dir)
		return ;
	get_redirlst(temp_dir, curr_dir, dir_list, lst);
	closedir(temp_dir);
}

void	get_expand_direct(t_list **lst, t_list *path)
{
	struct dirent	*entity;
	DIR				*directory;
	char			*filename;

	directory = opendir(".");
	if (!directory)
		return ;
	entity = readdir(directory);
	filename = ft_strdup(((t_expansion *)path->content)->file);
	while (entity)
	{
		if (file_cmp(entity->d_name, filename) && dir_type(entity->d_type))
		{
			free(((t_expansion *)path->content)->file);
			((t_expansion *)path->content)->file = ft_strdup(entity->d_name);
			push_to_redirlst(path, lst, ((t_expansion *)path->content)->file);
		}
		entity = readdir(directory);
	}
	free(filename);
	closedir(directory);
}

void	get_full_redirlst(DIR *temp_dir, char *dir, t_list *path, t_list **lst)
{
	char			*next_dir;
	struct dirent	*entity;

	entity = readdir(temp_dir);
	while (entity)
	{
		if (file_cmp(get_file(path->next), entity->d_name) && \
			dir_type(entity->d_type))
		{
			next_dir = get_path(entity->d_name, dir);
			if (next_dir)
			{
				push_to_redirlst(path, lst, next_dir);
				free(next_dir);
			}
		}
		entity = readdir(temp_dir);
	}
}

void	push_to_redirlst(t_list *path, t_list **lst, char *dir)
{
	DIR	*temp_dir;

	if (!path->next->next)
	{
		add_redirlst(dir, path->next, lst);
		return ;
	}
	temp_dir = opendir(dir);
	if (!temp_dir)
		return ;
	get_full_redirlst(temp_dir, dir, path, lst);
	closedir(temp_dir);
}
