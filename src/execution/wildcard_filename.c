/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:03:52 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 21:43:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	no_star_part(char *text)
{
	size_t	len;

	len = 0;
	while (text[len] != '*' && text[len] != '\0')
		len++;
	return (len);
}

char	*ft_strstr(char *haystack, char *needle)
{
	char	*substr;
	size_t	i;

	if (!haystack || !needle)
		return (NULL);
	i = ft_strlen(needle);
	substr = ft_strchr(haystack, needle[0]);
	while (substr && ft_strncmp(substr, needle, i))
		substr = ft_strchr(substr + 1, needle[0]);
	if (!substr)
		return (NULL);
	return (substr);
}

int	file_list_comparison(char *search, char *files)
{
	char	*match;

	if (*search == '*')
	{
		while (*search == '*')
			search++;
		if (!*search)
			return (1);
		match = ft_substr(search, 0, no_star_part(search));
		files = ft_strstr(files, match);
		free(match);
		if (!files)
			return (0);
	}
	while (*files && *search && *search == *files)
	{
		search++;
		files++;
	}
	if ((!*search && !*files) || (*search == '*' && *(search + 1) == '\0'))
		return (1);
	if (*search == '*')
		return (file_list_comparison(search, files));
	return (0);
}

int	file_cmp(char *search, char	*files)
{
	if (!files || ! search)
		return (0);
	if (ft_strcmp(search, files) == 0)
		return (1);
	if (!ft_strcmp(files, ".") || !ft_strcmp(files, ".."))
		return (0);
	return (file_list_comparison(search, files));
}
