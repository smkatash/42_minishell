/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_termios.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:13:31 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/24 13:00:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TERMIOS_H
# define MS_TERMIOS_H

void	cancel_echoctl(struct termios *termios_cpy);
void	reset_echoctl(struct termios *termios_cpy);

#endif
