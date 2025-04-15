
.PHONY: all clean fclean re

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

HEADER = type.h lexer.h parser.h

SRC = lexer.c 					\
      lexer_utils.c 			\
	  buffer_dynamic.c			\
	  group_tokens.c			\
	  heredoc_handle.c			\
	  expand.c					\
	  parser.c					\
	  generate_temp_filename.c	\
      print_var.c	 			\
      main.c			

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

