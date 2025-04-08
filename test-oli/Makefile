
.PHONY: all clean fclean re

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADER = mini.h lexer.h

SRC = commande.c \
      lexer.c \
      parser.c \
      lexer_utils.c \
	  group_tokens.c \
      token.c \
      main.c	\
	  buffer_dynamic.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

