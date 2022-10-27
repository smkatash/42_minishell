/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_table1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:40:23 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_and_or(void (***table)(t_list **, enum e_grammar ))
{
	table[NT_START][T_LBRACE - NONTERM] = &run_start;
	table[NT_START][T_STRING - NONTERM] = &run_start;
	table[NT_START][T_ASSIGN - NONTERM] = &run_start;
	table[NT_START][T_LESS - NONTERM] = &run_start;
	table[NT_START][T_GREAT - NONTERM] = &run_start;
	table[NT_START][T_DGREAT - NONTERM] = &run_start;
	table[NT_START][T_LESSGREAT - NONTERM] = &run_start;
	table[NT_START][T_DLESS - NONTERM] = &run_start;
	table[NT_AND_OR][T_LBRACE - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_STRING - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_ASSIGN - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_LESS - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_GREAT - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_DGREAT - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_LESSGREAT - NONTERM] = &run_and_or;
	table[NT_AND_OR][T_DLESS - NONTERM] = &run_and_or;
	table[NT_AND_OR1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_AND_OR1][T_AND - NONTERM] = &run_and_or1;
	table[NT_AND_OR1][T_OR - NONTERM] = &run_and_or1;
	table[NT_AND_OR1][T_RBRACE - NONTERM] = &set_epsilon;
}

void	pipe_and_subshell(void (***table)(t_list **, enum e_grammar))
{
	table[NT_PIPESPLIT][T_AND - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_OR - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_LBRACE - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_STRING - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_ASSIGN - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_LESS - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_GREAT - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_DGREAT - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_LESSGREAT - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT][T_DLESS - NONTERM] = &run_pipe;
	table[NT_PIPESPLIT1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_PIPESPLIT1][T_AND - NONTERM] = &set_epsilon;
	table[NT_PIPESPLIT1][T_OR - NONTERM] = &set_epsilon;
	table[NT_PIPESPLIT1][T_PIPE - NONTERM] = &run_pipe1;
	table[NT_PIPESPLIT1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_SUBSHELL][T_LBRACE - NONTERM] = &run_subshell;
}

void	split_to_prefix(void (***table)(t_list **, enum e_grammar))
{
	table[NT_PREFIX][T_ASSIGN - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX][T_LESS - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX][T_GREAT - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX][T_DGREAT - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX][T_LESSGREAT - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX][T_DLESS - NONTERM] = &run_prefix_with_cmd;
	table[NT_PREFIX1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_AND - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_OR - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_STRING - NONTERM] = &set_epsilon;
	table[NT_PREFIX1][T_LESS - NONTERM] = &run_prefix_with_cmd1;
	table[NT_PREFIX1][T_GREAT - NONTERM] = &run_prefix_with_cmd1;
	table[NT_PREFIX1][T_DGREAT - NONTERM] = &run_prefix_with_cmd1;
	table[NT_PREFIX1][T_LESSGREAT - NONTERM] = &run_prefix_with_cmd1;
	table[NT_PREFIX1][T_DLESS - NONTERM] = &run_prefix_with_cmd1;
	table[NT_IO_REDIR][T_LESS - NONTERM] = &run_io_file;
	table[NT_IO_REDIR][T_GREAT - NONTERM] = &run_io_file;
	table[NT_IO_REDIR][T_DGREAT - NONTERM] = &run_io_file;
	table[NT_IO_REDIR][T_LESSGREAT - NONTERM] = &run_io_file;
	table[NT_IO_REDIR][T_DLESS - NONTERM] = &run_io_file;
}

void	run_redirections_grand(void (***table)(t_list **, enum e_grammar))
{
	table[NT_REDIR][T_LESS - NONTERM] = &run_redirections;
	table[NT_REDIR][T_GREAT - NONTERM] = &run_redirections;
	table[NT_REDIR][T_DGREAT - NONTERM] = &run_redirections;
	table[NT_REDIR][T_LESSGREAT - NONTERM] = &run_redirections;
	table[NT_REDIR][T_DLESS - NONTERM] = &run_redirections;
	table[NT_REDIR1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_REDIR1][T_AND - NONTERM] = &set_epsilon;
	table[NT_REDIR1][T_OR - NONTERM] = &set_epsilon;
	table[NT_REDIR1][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_REDIR1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_REDIR1][T_LESS - NONTERM] = &run_redirections1;
	table[NT_REDIR1][T_GREAT - NONTERM] = &run_redirections1;
	table[NT_REDIR1][T_DGREAT - NONTERM] = &run_redirections1;
	table[NT_REDIR1][T_LESSGREAT - NONTERM] = &run_redirections1;
	table[NT_REDIR1][T_DLESS - NONTERM] = &run_redirections1;
}
