/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:57:57 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 21:43:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redirlst(DIR *temp_dir, char *dir, t_list *path, t_list **lst)
{
	t_expansion		*file;
	struct dirent	*entity;
	char			*folder;
	t_list			*new_lst;

	entity = readdir(temp_dir);
	while (entity)
	{
		file = (t_expansion *)path->content;
		if (file_cmp(file->file, entity->d_name) \
			&& dir_type_checker(file->type, entity->d_type))
		{
			if (!dir)
				folder = ft_strdup(entity->d_name);
			else
				folder = get_path(entity->d_name, dir);
			new_lst = ft_lstnew(folder);
			ft_lstadd_back(lst, new_lst);
		}
		entity = readdir(temp_dir);
	}
}

/* write function for freeing &free_get_listed */
t_list	*expand_star(char *str)
{
	t_list		*get_listed;
	t_list		*new_lst;
	t_expansion	*file;
	int			list_len;

	if (!str)
		return (NULL);
	new_lst = NULL;
	get_listed = get_path_for_expansion(str);
	if (!get_listed)
		return (NULL);
	file = (t_expansion *)get_listed->content;
	list_len = ft_lstsize(get_listed);
	if (list_len > 1 && ft_strchr(file->file, '*'))
		get_expand_direct(&new_lst, get_listed);
	else if (!get_listed->next)
		add_redirlst(NULL, get_listed, &new_lst);
	else
		push_to_redirlst(new_lst, &get_listed, file->file);
	ft_lstclear(&get_listed, &free_expansion_file_struct);
	return (new_lst);
}

void	merge_to_list(t_list **curr_lst, t_list *new, \
	t_list *prev, t_list **lst)
{
	t_list	*temp;
	t_list	*update_lst;

	if (prev)
	{
		prev->next = new;
		temp = ft_lstlast(new);
		temp->next = (*curr_lst)->next;
	}
	else
	{
		temp = ft_lstlast(new);
		*lst = new;
		temp->next = (*curr_lst)->next;
	}
	update_lst = *curr_lst;
	*curr_lst = ft_lstlast(new);
	ft_lstdelone(update_lst, &free);
}

void	filename_expansion(t_list **redir_list)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*new;

	curr = *redir_list;
	prev = NULL;
	while (curr)
	{
		if (curr->content && ft_strchr((char *)curr->content, '*'))
		{
			new = expand_star((char *)curr->content);
			if (new)
				merge_to_list(&curr, new, prev, redir_list);
		}
		prev = curr;
		curr = curr->next;
	}
}
