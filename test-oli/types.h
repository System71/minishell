#ifndef TYPE_H
#define TYPE_H

#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <readline/history.h>
/***********************************/
/**********     LEXER    **********/
typedef struct s_dynamic_buffer {
    char   *data;
    size_t capacity;
    size_t len;
} t_dynamic_buffer;

typedef enum e_quote_type {
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
} t_quote_type;

typedef enum e_token_type {
    T_WORD,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND,
    T_HEREDOC,
    T_PIPE
} t_token_type;

/* Structure représentant un segment de texte dans un token.
   Un segment est une portion de texte avec un contexte de quote précis. */
typedef struct s_token_segment {
    char *content;
    t_quote_type quote;             // Contexte : non cité, quote simple ou quote double
    struct s_token_segment *next;   // Segment suivant dans le même token (s'il existe)
} t_token_segment;

/* Structure représentant un token. Pour les tokens de type T_WORD,
   on stocke une liste de segments pour pouvoir gérer les cas complexes
   où différentes portions du token proviennent de contextes différents. */
typedef struct s_token {
    t_token_type type;          // Par exemple : T_WORD, T_PIPE, etc.
    t_token_segment *segments;  // Liste chaînée des segments constituant ce token
    struct s_token *next;       // Token suivant dans la liste globale
} t_token;

typedef enum e_lexer_state {
    LEXER_NORMAL,
    LEXER_SINGLE_QUOTE,
    LEXER_DOUBLE_QUOTE
} t_lexer_state;

typedef struct s_utils_lexer{
	t_lexer_state		state;
	int					i;
	char				c;
	t_dynamic_buffer	*buffer;
    t_quote_type		current_quote;
	bool				new_arg;
} t_utils_lexer;
/***********************************/
/**********     PARSER    **********/
typedef struct s_redirection
{
	int type; // Par exemple, T_REDIRECT_IN, T_REDIRECT_OUT, T_APPEND, T_HEREDOC 
	char *target; // Le fichier(avec son chemin pour le heredoc) 
	struct s_redirection *next;
} t_redirection;

typedef struct s_command
{
	char **args; // Tableau dynamique ou liste chaînée des arguments
	t_redirection *redirs; // Liste des redirections associées
	struct s_command *next; // Pour chaîner les commandes d'un pipeline
} t_command;

#endif
