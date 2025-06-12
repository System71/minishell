SRC_DIR        = src/
PARSING_DIR    = $(SRC_DIR)parsing/
EXECUTION_DIR    = $(SRC_DIR)execution/
MEMORY_DIR    = $(SRC_DIR)memory/
ERROR_DIR    = $(SRC_DIR)error/
PARSING_UTILS  = lib/parsing_utils/
LIBFT_DIR      = lib/libft/

SRC = \
    $(SRC_DIR)main.c \
    $(SRC_DIR)init_minishell.c \
    $(SRC_DIR)utils.c \
    \
   $(PARSING_DIR)lexer.c \
    $(PARSING_DIR)parsing.c \
    $(PARSING_DIR)parser.c \
    $(PARSING_DIR)cmd_list.c \
    $(PARSING_DIR)buffer_dynamic.c \
    $(PARSING_DIR)expand.c \
    $(PARSING_DIR)generate_temp_filename.c \
    $(PARSING_DIR)group_tokens.c \
    $(PARSING_DIR)heredoc_handle.c \
    $(PARSING_DIR)lexer_flush.c \
    $(PARSING_DIR)lexer_normal.c \
    $(PARSING_DIR)lexer_quote.c \
    $(PARSING_DIR)token_list.c \
    $(PARSING_DIR)create_token.c \
    $(PARSING_DIR)split_handle.c \
    $(PARSING_DIR)print_var.c \
    \
	$(EXECUTION_DIR)execute_and_cleanup.c \
    $(EXECUTION_DIR)signals.c \
    $(EXECUTION_DIR)new_pipex.c \
    $(EXECUTION_DIR)new_pipex_utils.c \
    $(EXECUTION_DIR)builtin.c \
    $(EXECUTION_DIR)export.c \
    $(EXECUTION_DIR)unset.c \
    $(EXECUTION_DIR)change_env_utils.c \
    $(EXECUTION_DIR)cmd_process.c \
    $(EXECUTION_DIR)cd.c \
    $(EXECUTION_DIR)exit.c \
    $(EXECUTION_DIR)oliv_exec.c \
    \
    $(MEMORY_DIR)ft_xmalloc.c \
    $(MEMORY_DIR)free_child.c \
	$(ERROR_DIR)error_parsing_return.c\
	$(ERROR_DIR)error_synthaxe.c\
	$(ERROR_DIR)is_error.c\
    \
    $(PARSING_UTILS)ft_isalnum.c \
    $(PARSING_UTILS)ft_isalpha.c \
    $(PARSING_UTILS)ft_isdigit.c \
    $(PARSING_UTILS)ft_iswhitespace.c \
    $(PARSING_UTILS)ft_memcpy.c \
    $(PARSING_UTILS)ft_realloc.c \
    $(PARSING_UTILS)ft_strdup_oli.c \
    $(PARSING_UTILS)ft_strcat.c \
    $(PARSING_UTILS)ft_strndup_oli.c \
    $(PARSING_UTILS)ft_strcpy.c \
    $(PARSING_UTILS)ft_strcmp.c \
    $(PARSING_UTILS)ft_itoa.c \
    $(PARSING_UTILS)get_int_size.c \
    $(PARSING_UTILS)append_all.c \
    $(PARSING_UTILS)heredoc_utils.c \
    $(PARSING_UTILS)expand_utils.c \
    $(PARSING_UTILS)is_fonction.c \
    $(PARSING_UTILS)ft_strchr.c \
    $(PARSING_UTILS)ft_split.c \
    $(PARSING_UTILS)ft_strlen.c

HEADERS = \
		   includes/minishell.h \
			includes/types.h \
			includes/ft_printf.h \
			includes/get_next_line.h \
			includes/libft.h 

