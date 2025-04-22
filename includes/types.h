#ifndef TYPE_H
# define TYPE_H

# include <stdlib.h>
# include <stdbool.h>
/***********************************/
/**********     LEXER    **********/
typedef struct s_dynamic_buffer
{
	char					*data;
	size_t					capacity;
	size_t					len;
}							t_dynamic_buffer;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}							t_quote_type;

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_PIPE
}							t_token_type;

typedef struct s_token_segment
{
	char					*content;
	t_quote_type			quote;
	struct s_token_segment	*next;
}							t_token_segment;

typedef struct s_token
{
	t_token_type type;
	t_token_segment			*segments;
	struct s_token *next;
}							t_token;

typedef enum e_lexer_state
{
	LEXER_NORMAL,
	LEXER_SINGLE_QUOTE,
	LEXER_DOUBLE_QUOTE
}							t_lexer_state;

typedef struct s_utils_lexer
{
	t_lexer_state			state;
	int						i;
	char					c;
	t_dynamic_buffer		*buffer;
	t_quote_type			current_quote;
	bool					new_arg;
}							t_utils_lexer;
/***********************************/
/**********     PARSER    **********/
typedef struct s_redirection
{
	int						type;
	char *target;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char **args;
	t_redirection *redirs;
	pid_t					pid;
	int						*status;
	struct s_command *next;
}							t_command;
/***********************************/
/**********     FILENAME    **********/
typedef struct s_tempfile
{
    int     fd;
    int     counter;
    int     len;
    char    *filename;
}							t_tempfile;
/***********************************/
/**********     EXPAND    **********/
typedef struct s_expand_vars
{
    char    *result;
    char    tmp[2];
    size_t  i;
    size_t  start;
    size_t  len;
    char    *name;
    char    *value;
    char    *buf;
}               t_expand_vars;

/***********************************/
/**********     HEREDOC    **********/
typedef struct s_heredoc
{
    char    *delimiter;
    char    *content;
    size_t  content_len;
    size_t  line_count;
}           t_heredoc;
#endif
