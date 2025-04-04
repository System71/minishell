#ifndef MINI_H
#define MINI_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

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

typedef enum e_lexer_state {
    LEXER_NORMAL,
    LEXER_SINGLE_QUOTE,
    LEXER_DOUBLE_QUOTE
} t_lexer_state;

typedef struct s_utils_lexer{
	t_lexer_state	state;
	int				buf_index;
	int				i;
	char			c;
	char			buffer[BUFFER_SIZE];
	bool			spl_quote_open;
	bool			dbl_quote_open;

} t_utils_lexer;

int				is_special_char(char c);
t_token			*add_token(t_token *list, char *content);
void			flush_buffer(t_utils_lexer *storage, t_token **tokens);
t_token_type	get_token_type(const char *str);
const char		*token_type_to_string(t_token_type type);
void			print_tokens(t_token *tokens);

// LEXER


t_token *lexer(const char *input);


// LEXER UTILS
void			process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens);
void			process_quote_char(t_utils_lexer *storage);
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
void       add_argument(t_command *cmd, t_token *token, t_token_type type);
void       print_commands(t_command *cmd_list);

// PARSER
t_command *parser(t_token *tokens);


#endif
