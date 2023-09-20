# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 23:43:05 by luide-so          #+#    #+#              #
#    Updated: 2023/09/20 00:12:43 by luide-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=thread
INC		=	-I include
RM		=	rm -rf

OBJ_DIR	=	obj
VPATH	=	src

_FILES	=	main \
			utils
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

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
