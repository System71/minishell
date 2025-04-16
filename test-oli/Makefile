# **************************************************************************** #
#                                   Makefile                                    #
# **************************************************************************** #

.PHONY: all clean fclean re

# Nom de l'exécutable
NAME        = minishell

# Compilateur et options
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# Headers du projet (modifiez si nécessaire)
HEADER      = type.h lexer.h parser.h includes/lib_utils.h

# Sources de la partie "librairie"
SRC_LIB     = \
	lib_utils/ft_realloc.c \
	lib_utils/ft_strdup.c \
	lib_utils/ft_strlen.c  \
	lib_utils/ft_memcpy.c

# Sources principales
SRC         = \
	lexer.c \
	lexer_utils.c \
	buffer_dynamic.c \
	group_tokens.c \
	heredoc_handle.c \
	expand.c \
	parser.c \
	generate_temp_filename.c \
	print_var.c \
	main.c

# Répertoire où seront stockés les fichiers objets
OBJ_DIR     = obj

# Fusion de toutes les sources en une seule liste
ALL_SRC     = $(SRC) $(SRC_LIB)

# Génération des chemins objet correspondants
# Exemple : lib_utils/ft_realloc.c => obj/lib_utils/ft_realloc.o
OBJ         = $(ALL_SRC:%.c=$(OBJ_DIR)/%.o)

# Règle par défaut
all: $(NAME)

# Édition de liens
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

# Règle générique de compilation :
# - crée d'abord le sous-dossier nécessaire dans obj/
# - compile ensuite le .c en .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des objets
clean:
	rm -rf $(OBJ_DIR)

# Nettoyage des objets + exécutable
fclean: clean
	rm -f $(NAME)

# Reconstruit tout
re: fclean all

