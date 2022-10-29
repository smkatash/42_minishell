# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/10/29 15:05:20 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src/builtins src/destructor src/environment src/error src/execution src/expansion src/interpreter\
			src/signals src/interpreter/ast src/interpreter/lexer src/interpreter/parser src/interpreter/syntax\
			src/interpreter/tokenizer
INCFL	=	-I libs/ibft -I include -I libs/libgnL

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

NAME	=	minishell
SRC		=	main.c\
			builtin_utils.c builtins.c mini_cd.c mini_echo.c mini_env.c\
			mini_exit.c mini_export.c mini_pwd.c mini_unset.c\
			redirections_builtin.c\
			add_to_env.c env_free.c env_init.c env_print_tree.c env_tree.c\
			env_utils.c make_envp.c update_env.c execute_and_or_cmd.c\
			execute_assignment.c execute_heredoc.c\
			execute_commands_and_pipes.c execute_redirection.c\
			execute_utils.c list_to_argv.c main_execution.c path.c\
			main_execution_utils.c run_processes.c run_cmd.c\
			wildcard_bonus.c wildcard_filename.c wildcard_path.c wildcard_traverse.c\
			wildcard_utils.c buf_utils.c dollarsign.c exp_utils.c expander.c quote_removal.c\
			tilde.c exp_here.c expand_cmd.c\
			ast_builder.c ast_builder_utils.c char_lexer.c\
			init_shell.c lexer.c lexer_utils.c\
			syntax_table1.c syntax_table2.c parser.c parser_utils.c\
			tokenizer.c tokenizer_utils.c \
			traverse_utils.c tree_traverse1.c tree_traverse2.c tree_traverse3.c\
			tree_traverse4.c tree_traverse5.c\
			signals_interactive.c signals_parent.c signals_child.c\
			signal_print.c ms_termios.c\
			destroy1.c destroy2.c error1.c error2.c error3.c\
			print_error.c exit_minishell.c
LIBS	=	libs/libft/libft.a
LIBSGNL	=	libs/gnL/libgnL.a
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

.SILENT:

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS) $(LIBSGNL)
	$(CC) $(CFLAGS) -o $@ $^ -Llibs/libft -lft -Llibs/gnL -lgnL -lreadline -ltermcap #-fsanitize=address
	@echo "minishell is compiled"

obj/%.o : %.c | obj
	$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj :
	mkdir obj

$(LIBS) :
	- (cd libs/libft && make bonus && make clean)

$(LIBSGNL) :
	- (cd libs/gnL && make && make clean)

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)
	-(cd libs/libft && make fclean)
	-(cd libs/gnL && make fclean)

re : clean all

mini: $(NAME)
	./$(NAME)

.PHONY : all clean fclean re

