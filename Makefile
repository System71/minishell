# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 13:04:53 by prigaudi          #+#    #+#              #
#    Updated: 2025/04/10 11:28:15 by prigaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -I includes/

LIBFT_DIR = ./src/libft
LIBFT = $(LIBFT_DIR)/libft.a

PIPEX_DIR = ./src/pipex
PIPEX = $(PIPEX_DIR)/pipex

SRC_DIR = src
SRC = 		$(SRC_DIR)/main.c			\
			$(SRC_DIR)/signals.c		\
			$(SRC_DIR)/builtin.c		\
			$(SRC_DIR)/change_env.c		\
			$(SRC_DIR)/non_built.c		\
			$(SRC_DIR)/cmd_process.c	\
			$(SRC_DIR)/cd.c				\
			$(SRC_DIR)/utils.c

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: make_libft make_pipex $(NAME)

$(NAME): $(LIBFT) $(PIPEX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/minishell.h Makefile | $(OBJ_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

make_libft:
	make -C $(LIBFT_DIR) --no-print-directory

make_pipex :
	make -C $(PIPEX_DIR) --no-print-directory

clean:
	find . -name $(OBJ_DIR) -type d -exec rm -rf {} +
fclean: clean
	rm -f $(NAME)
re: fclean all