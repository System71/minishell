# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 14:27:24 by prigaudi          #+#    #+#              #
#    Updated: 2025/04/03 09:43:01 by prigaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus
NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -I ../../includes

SRC = 			ft_atoi.c					\
      			ft_bzero.c					\
      			ft_calloc.c					\
      			ft_isalnum.c				\
	  			ft_isalpha.c				\
	  			ft_isascii.c				\
	  			ft_isdigit.c				\
	  			ft_isprint.c				\
	  			ft_itoa.c					\
	  			ft_memset.c					\
	  			ft_memcpy.c					\
	  			ft_memmove.c				\
	  			ft_memchr.c					\
	  			ft_memcmp.c					\
	  			ft_putchar_fd.c				\
	  			ft_putstr_fd.c				\
	  			ft_putendl_fd.c				\
	  			ft_putnbr_fd.c				\
	  			ft_split.c					\
	  			ft_strchr.c					\
	  			ft_striteri.c				\
	  			ft_strjoin.c				\
	  			ft_strdup.c					\
	 			ft_strlcat.c				\
	  			ft_strlcpy.c				\
	  			ft_strlen.c					\
	  			ft_strmapi.c				\
	  			ft_strncmp.c				\
	  			ft_strnstr.c				\
	  			ft_strrchr.c				\
	  			ft_strtrim.c				\
	  			ft_substr.c					\
	  			ft_tolower.c				\
	  			ft_toupper.c

SRC_GNL =		get_next_line.c				\
				get_next_line_utils.c		

SRC_PRINTF =	ft_base.c					\
				ft_character.c				\
				ft_decimal.c				\
				ft_pointer.c				\
				ft_printf.c					\
				ft_string.c					

SRCBONUS = 		ft_lstnew_bonus.c			\
				ft_lstadd_front_bonus.c		\
				ft_lstsize_bonus.c			\
				ft_lstlast_bonus.c			\
				ft_lstadd_back_bonus.c		\
				ft_lstdelone_bonus.c		\
				ft_lstclear_bonus.c			\
				ft_lstiter_bonus.c			\
				ft_lstmap_bonus.c			

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_GNL = $(SRC_GNL:%.c=$(OBJ_DIR)/gnl/%.o)
OBJ_PRINTF = $(SRC_PRINTF:%.c=$(OBJ_DIR)/printf/%.o)
OBJBONUS = $(SRCBONUS:.c=.o)

VPATH = src:gnl:printf

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL) $(OBJ_PRINTF)
	ar rcs $@ $^
	
$(OBJ_DIR)/%.o: %.c ../../includes/libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/gnl/%.o: %.c ../../includes/get_next_line.h | $(OBJ_DIR)/gnl
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gnl:
	mkdir -p $(OBJ_DIR)/gnl

$(OBJ_DIR)/printf/%.o: %.c ../../includes/ft_printf.h | $(OBJ_DIR)/printf
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/printf:
	mkdir -p $(OBJ_DIR)/printf

bonus: $(OBJ) $(OBJBONUS)
	ar rcs $(NAME) $^

clean:
	find . -name $(OBJ_DIR) -type d -exec rm -rf {} +
fclean: clean
	rm -f $(NAME)
re: fclean all