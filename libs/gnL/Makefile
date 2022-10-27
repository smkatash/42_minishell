# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 16:48:28 by ktashbae          #+#    #+#              #
#    Updated: 2022/09/22 16:56:09 by ktashbae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc
FLAGS = -Wall -Wextra -Werror
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h
NAME = libgnL.a

all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus