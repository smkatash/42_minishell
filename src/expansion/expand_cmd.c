/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:39:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/29 20:15:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_string_enomem(char *message, int error_flag)
{
	g_global_exit_status = ENOMEM;
	expansion_error(message, error_flag);
	return (1);
}

void	expand_lst_delone(t_list **lst_of_strings, t_list **trav, \
	t_list **prev, char *new_content)
{
	free(new_content);
	if (*trav == *lst_of_strings)
	{
		*lst_of_strings = (*trav)->next;
		ft_lstdelone(*trav, &free);
		*prev = *lst_of_strings;
		*trav = *prev;
	}
	else
	{
		(*prev)->next = (*trav)->next;
		ft_lstdelone(*trav, &free);
		*trav = *prev;
		if (*trav != NULL)
			*trav = (*trav)->next;
	}
}

static bool	completely_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

static void	expand_list_continue(char *new_content, t_list **trav, \
	t_list **prev)
{
	free((*trav)->content);
	(*trav)->content = new_content;
	*prev = *trav;
	*trav = (*trav)->next;
}

int	expand_list_cmd(t_list **lst_of_strings, t_env *env, int status, \
	int error_flag)
{
	t_list	*prev;
	t_list	*trav;
	char	*new_content;

	if (status)
		return (1);
	trav = *lst_of_strings;
	prev = trav;
	while (trav != NULL)
	{
		new_content = expand_string(trav->content, env, LEAVE_QUOTES);
		if (new_content == NULL)
			return (expand_string_enomem((*lst_of_strings)->content, \
			error_flag));
		if (completely_empty(new_content))
			expand_lst_delone(lst_of_strings, &trav, &prev, new_content);
		else
		{
			new_content = cmd_rm_quotes(new_content);
			expand_list_continue(new_content, &trav, &prev);
		}
	}
	return (0);
}
