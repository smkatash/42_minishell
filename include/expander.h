/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/29 21:17:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ms_typedefs.h"

typedef struct s_char_buf
{
	char	*buf;
	int		size;
	int		free;
}			t_char_buf;

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define RM_QUOTES 1
# define LEAVE_QUOTES 0

# define BUFSIZE 128

/* expander.c */
char		*expand_string(char *s, t_env *env, bool rm_quotes);
int			expander(t_list *nodes, t_env *env);

/* expand_cmd.c*/
int			expand_string_enomem(char *message, int error_flag);
void		expand_lst_delone(t_list **lst_of_strings, t_list **trav, \
t_list **prev, char *new_content);
int			expand_list_cmd(t_list **lst_of_strings, t_env *env, int status, \
int error_flag);

/* dollarsign.c */
bool		is_end_of_key(char c);
char		*expand_substr_ds(t_env *env, t_char_buf *buf, char *ptr);
void		expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf);

/* quote_removal.c */
void		exp_remove_quotes(t_char_buf *buf);
char		*cmd_rm_quotes(char *s);

/* tilde.c */
void		expand_tilde(t_env *env, t_char_buf *buf);

/* buf_utils.c */
void		init_char_buf(t_char_buf *buf);
void		resize_buffer(t_char_buf *buf);
void		add_char_to_buf(t_char_buf *buf, char c);
void		add_str_to_buf(t_char_buf *buf, char *s);

/* exp_utils.c */
int			change_quote_modus(int *quote_modus, char quote_found);

/* exp_here.c */
char		*heredoc_rm_quotes(char *delim);
char		*expand_here(t_env *env, char *s);
#endif
