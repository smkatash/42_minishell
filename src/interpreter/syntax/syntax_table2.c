/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_table2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:13:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/26 19:06:55 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commandset_and_io_here_file(void (***table)(t_list **, enum e_grammar))
{
	table[NT_COMMANDSET][T_LBRACE - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_STRING - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_ASSIGN - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_LESS - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_GREAT - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_DGREAT - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_LESSGREAT - NONTERM] = &run_commandset;
	table[NT_COMMANDSET][T_DLESS - NONTERM] = &run_commandset;
	table[NT_COMMANDSET1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_COMMANDSET1][T_AND - NONTERM] = &set_epsilon;
	table[NT_COMMANDSET1][T_OR - NONTERM] = &set_epsilon;
	table[NT_COMMANDSET1][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_COMMANDSET1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_COMMANDSET1][T_LESS - NONTERM] = &run_commandset1;
	table[NT_COMMANDSET1][T_GREAT - NONTERM] = &run_commandset1;
	table[NT_COMMANDSET1][T_DGREAT - NONTERM] = &run_commandset1;
	table[NT_COMMANDSET1][T_LESSGREAT - NONTERM] = &run_commandset1;
	table[NT_COMMANDSET1][T_DLESS - NONTERM] = &run_commandset1;
	table[NT_IO_FILE][T_LESS - NONTERM] = &redirect_to_file;
	table[NT_IO_FILE][T_GREAT - NONTERM] = &redirect_to_file;
	table[NT_IO_FILE][T_DGREAT - NONTERM] = &redirect_to_file;
	table[NT_IO_FILE][T_LESSGREAT - NONTERM] = &redirect_to_file;
	table[NT_IO_FILE][T_DLESS - NONTERM] = &redirect_to_file;
	table[NT_IO_HERE][T_DLESS - NONTERM] = &run_io_here;
}

void	get_suffix_cmd(void (***table)(t_list **, enum e_grammar))
{
	table[NT_SUFFIX][T_STRING - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX][T_LESS - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX][T_GREAT - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX][T_DGREAT - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX][T_LESSGREAT - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX][T_DLESS - NONTERM] = &run_cmd_suffix;
	table[NT_SUFFIX1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_SUFFIX1][T_AND - NONTERM] = &set_epsilon;
	table[NT_SUFFIX1][T_OR - NONTERM] = &set_epsilon;
	table[NT_SUFFIX1][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_SUFFIX1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_SUFFIX1][T_STRING - NONTERM] = &run_cmd_suffix1;
	table[NT_SUFFIX1][T_LESS - NONTERM] = &run_cmd_suffix1;
	table[NT_SUFFIX1][T_GREAT - NONTERM] = &run_cmd_suffix1;
	table[NT_SUFFIX1][T_DGREAT - NONTERM] = &run_cmd_suffix1;
	table[NT_SUFFIX1][T_LESSGREAT - NONTERM] = &run_cmd_suffix1;
	table[NT_SUFFIX1][T_DLESS - NONTERM] = &run_cmd_suffix1;
}

void	child_commands(void (***table)(t_list **, enum e_grammar))
{
	table[NT_CMD][T_STRING - NONTERM] = &run_command;
	table[NT_CMD][T_ASSIGN - NONTERM] = &run_command;
	table[NT_CMD][T_LESS - NONTERM] = &run_command;
	table[NT_CMD][T_GREAT - NONTERM] = &run_command;
	table[NT_CMD][T_DGREAT - NONTERM] = &run_command;
	table[NT_CMD][T_LESSGREAT - NONTERM] = &run_command;
	table[NT_CMD][T_DLESS - NONTERM] = &run_command;
	table[NT_CMD1][T_EOF - NONTERM] = &set_epsilon;
	table[NT_CMD1][T_AND - NONTERM] = &set_epsilon;
	table[NT_CMD1][T_OR - NONTERM] = &set_epsilon;
	table[NT_CMD1][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_CMD1][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_CMD1][T_STRING - NONTERM] = &run_command1;
	table[NT_CMD2][T_EOF - NONTERM] = &set_epsilon;
	table[NT_CMD2][T_AND - NONTERM] = &set_epsilon;
	table[NT_CMD2][T_OR - NONTERM] = &set_epsilon;
	table[NT_CMD2][T_PIPE - NONTERM] = &set_epsilon;
	table[NT_CMD2][T_RBRACE - NONTERM] = &set_epsilon;
	table[NT_CMD2][T_STRING - NONTERM] = &run_command2;
	table[NT_CMD2][T_LESS - NONTERM] = &run_command2;
	table[NT_CMD2][T_GREAT - NONTERM] = &run_command2;
	table[NT_CMD2][T_DGREAT - NONTERM] = &run_command2;
	table[NT_CMD2][T_LESSGREAT - NONTERM] = &run_command2;
	table[NT_CMD2][T_DLESS - NONTERM] = &run_command2;
}
