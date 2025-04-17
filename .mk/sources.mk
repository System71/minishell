SRC_DIR        = src/
PARSING_DIR    = $(SRC_DIR)parsing/
PARSING_UTILS  = lib/parsing_utils/
LIBFT_DIR      = lib/libft/
PIPEX_DIR      = lib/pipex/

SRC = \
    $(SRC_DIR)main.c \
    $(SRC_DIR)signals.c \
    $(SRC_DIR)builtin.c \
    $(SRC_DIR)change_env.c \
    $(SRC_DIR)non_built.c \
    $(SRC_DIR)cmd_process.c \
    $(SRC_DIR)cd.c \
    $(SRC_DIR)utils.c \
    \
    $(PARSING_DIR)buffer_dynamic.c \
    $(PARSING_DIR)expand.c \
    $(PARSING_DIR)generate_temp_filename.c \
    $(PARSING_DIR)group_tokens.c \
    $(PARSING_DIR)heredoc_handle.c \
    $(PARSING_DIR)lexer_utils.c \
    $(PARSING_DIR)lexer.c \
    $(PARSING_DIR)parser.c \
    $(PARSING_DIR)print_var.c \
    \
    $(PARSING_UTILS)ft_isalnum.c \
    $(PARSING_UTILS)ft_isalpha.c \
    $(PARSING_UTILS)ft_isdigit.c \
    $(PARSING_UTILS)ft_memcpy.c \
    $(PARSING_UTILS)ft_realloc.c \
    $(PARSING_UTILS)ft_strdup.c \
    $(PARSING_UTILS)ft_strlen.c

HEADERS = \
		   includes/minishell.h \
			includes/lexer.h \
			includes/parser.h \
			includes/lib_utils.h \
			includes/types.h \
			includes/ft_printf.h \
			includes/get_next_line.h \
			includes/libft.h \
			includes/pipex.h \
			includes/signals.h

