#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define INITIAL_BUFFER_SIZE 64

typedef struct s_dynamic_buffer {
    char   *data;
    size_t capacity;
    size_t len;
} t_dynamic_buffer;

// TOKEN
#define BUFFER_SIZE 1024
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
    T_PIPE,
    T_DOLLAR
} t_token_type;

typedef struct s_token {
    t_token_type   type;
    char          *content;
	t_quote_type  quote;
    struct s_token *next;
} t_token;

typedef enum e_lexer_state {
    LEXER_NORMAL,
    LEXER_SINGLE_QUOTE,
    LEXER_DOUBLE_QUOTE
} t_lexer_state;

typedef struct s_utils_lexer{
	t_lexer_state		state;
	int					buf_index;
	int					i;
	char				c;
	t_dynamic_buffer	*buffer;
    t_quote_type		current_quote;
} t_utils_lexer;

int				is_special_char(char c);
t_token *add_token(t_token **list, const char *content, t_quote_type quote);
void			flush_buffer(t_utils_lexer *storage, t_token **tokens);
t_token_type	get_token_type(const char *str);

void			print_tokens(t_token *tokens);

// LEXER


t_token *lexer(const char *input);


// LEXER UTILS
void			process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens);
void			process_quote_char(t_utils_lexer *storage);

// DYNAMIC_BUFFER
t_dynamic_buffer *init_dynamic_buffer(void);
int append_char(t_dynamic_buffer *buf, char c);
void free_dynamic_buffer(t_dynamic_buffer *buf);

#endif

