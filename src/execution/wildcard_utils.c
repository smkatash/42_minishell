/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:41:29 by kanykei           #+#    #+#             */
/*   Updated: 2022/10/26 21:43:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_type_checker(enum e_type d_type, int type)
{
	if (d_type == type_dir)
	{
		type = dir_type(type);
		return (type);
	}
	return (1);
}

int	dir_type(unsigned char type)
{
	type = 4;
	return (type);
}

void	update_type_file(t_list	*lst)
{
	t_list		*last_file;
	t_expansion	*file;

	last_file = ft_lstlast(lst);
	file = (t_expansion *)last_file->content;
	file->type = type_file;
}

t_expansion	*init_file(char	*file, enum e_type type)
{
	t_expansion	*new_file;

	new_file = malloc(sizeof(t_expansion));
	if (!new_file)
		return (NULL);
	new_file->file = ft_strdup(file);
	if (!new_file->file)
	{
		free(new_file);
		return (NULL);
	}
	new_file->type = type;
	return (new_file);
}

char	*get_file(t_list *lst)
{
	t_expansion	*file;
	char		*name;

	file = (t_expansion *)lst->content;
	name = file->file;
	return (name);
}
