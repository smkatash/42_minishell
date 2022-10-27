/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:37:31 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/25 13:49:29 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

/* signals */
void	signals_interactive_mode(struct termios *termios_cpy);
void	signals_parent_process(void);
void	signals_child_process(struct termios *termios_cpy);
void	signals_child_heredoc(void);
void	parent_sigquit(void);
void	signal_print(int status);

/* terminal control */
void	cancel_echoctl(struct termios *termios_cpy);
void	reset_echoctl(struct termios *termios_cpy);

#endif