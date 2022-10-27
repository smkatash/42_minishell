/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:27:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 19:07:24 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Sets found variable according to the quote character that was found.
 * If the quotes_modus was NO_QUOTES, we are entering quotes, so quote_modus is
 * set to the modus of the quote found. If the quote_modus was equal to the 
 * quotes found, it means that we are closing quotes, so quote_modus is set back
 * to NO_QUOTES.In all other cases, we have single quotes within double quotes
 * or vice versa, they are read verbatim, thus quote_modus remains unchanged.
 * Function returns 1 if quote_modus was changed, 0 if it was left unchanged.
 */
int	change_quote_modus(int *quotes_modus, char quote_found)
{
	int	found;

	if (quote_found == '\'')
		found = SINGLE_QUOTES;
	else if (quote_found == '\"')
		found = DOUBLE_QUOTES;
	else
		return (0);
	if (*quotes_modus == NO_QUOTES)
	{
		*quotes_modus = found;
		return (1);
	}
	if (*quotes_modus == found)
	{
		*quotes_modus = NO_QUOTES;
		return (1);
	}
	return (0);
}
