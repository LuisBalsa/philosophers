# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 23:43:05 by luide-so          #+#    #+#              #
#    Updated: 2023/10/24 14:36:37 by luide-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread #-g -fsanitize=thread
INC		=	-I include
RM		=	rm -rf

OBJ_DIR	=	obj
VPATH	=	src

_FILES	=	main_bonus utils_bonus \
			philo_life_bonus
OBJS	=	$(_FILES:%=%.o)
TARGET	=	$(addprefix $(OBJ_DIR)/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(TARGET)
	echo Compiling $(NAME)
	$(CC) $(CFLAGS) $(TARGET) -o $(NAME) $(INC)
	echo Done.

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: all

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 4 410 200 200 1

.PHONY: all bonus clean fclean re

.SILENT:
