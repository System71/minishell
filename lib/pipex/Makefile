# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 13:04:53 by prigaudi          #+#    #+#              #
#    Updated: 2025/04/03 09:40:02 by prigaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -I ../../includes/

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC = 		$(SRC_DIR)/pipex.c						\
			$(SRC_DIR)/children.c					\
			$(SRC_DIR)/heredoc.c					\
			$(SRC_DIR)/utils.c						\
			$(SRC_DIR)/cmd.c

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: make_libft $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ../../includes/pipex.h Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

make_libft:
	make -C $(LIBFT_DIR) --no-print-directory

clean:
	find . -name "*.o" -type f -delete
	find . -type d -empty -delete
fclean: clean
	find . -name "*.a" -type f -delete
	rm -f $(NAME)
re: fclean all