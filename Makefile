# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 13:04:53 by prigaudi          #+#    #+#              #
#    Updated: 2025/03/24 13:31:33 by prigaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC = 		$(SRC_DIR)/main.c		\
			$(SRC_DIR)/signals.c

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: make_libft $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/minishell.h Makefile | $(OBJ_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

make_libft:
	make -C $(LIBFT_DIR) --no-print-directory

clean:
	find . -name $(OBJ_DIR) -type d -exec rm -rf {} +
fclean: clean
	rm -f $(NAME)
re: fclean all