#ifndef MINI_H
#define MINI_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TOKEN
#define BUFFER_SIZE 1024

typedef enum e_token_type {
    T_WORD,
    T_SINGLE_QUOTE,
    T_DOUBLE_QUOTE,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND,
    T_HEREDOC,
    T_PIPE,
    T_DOLLAR
} t_token_type;

typedef struct s_token {
    t_token_type   type;
    char          *content;
    struct s_token *next;
} t_token;

int				is_special_char(char c);
t_token			*create_empty_token_list(void);
t_token			*add_token(t_token *list, const char *content);
void			flush_buffer(char *buffer, int *buf_index, t_token **tokens);
t_token_type	get_token_type(const char *str);
const char		*token_type_to_string(t_token_type type);
void			print_tokens(t_token *tokens);

// LEXER
typedef enum e_lexer_state {
    LEXER_NORMAL,
    LEXER_SINGLE_QUOTE,
    LEXER_DOUBLE_QUOTE
} t_lexer_state;

t_token *lexer(const char *input);


// LEXER UTILS
void			process_normal_char(char c, const char *input, int *i, t_lexer_state *state, char *buffer, int *buf_index, t_token **tokens);
void			process_quote_char(char c, t_lexer_state *state, char *buffer, int *buf_index);
// COMMANDE
typedef struct s_command
{
    t_token_type     type;
	char           **argv;
    int              argc;
    struct s_command *next;
} t_command;

// Fonctions pour gérer la création et la manipulation de commandes
t_command *create_command(void);
void       add_argument(t_command *cmd, const char *arg);
void       print_commands(t_command *cmd_list);

// PARSER
t_command *parser(t_token *tokens);


#endif
