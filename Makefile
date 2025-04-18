# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 13:04:53 by prigaudi          #+#    #+#              #
#    Updated: 2025/04/17 11:04:22 by okientzl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re make_libft

NAME       := minishell
CC         := cc
CFLAGS     := -Wall -Werror -Wextra -g3 -I includes
OBJ_DIR    := obj

include .mk/sources.mk

OBJ_FILES  := $(SRC:.c=.o)
OBJ        := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: make_libft make_pipex $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

make_libft:
	make -C $(LIBFT_DIR) --no-print-directory

make_pipex :
	make -C $(PIPEX_DIR) --no-print-directory

clean:
	find . -name $(OBJ_DIR) -type d -exec rm -rf {} +

fclean: clean
	rm -f $(NAME)

re: fclean all
