#ifndef TYPE_H
# define TYPE_H

# include <stdbool.h>
# include <stdlib.h>
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
	T_PIPE,
	T_OR,
	T_AND,
	T_LPAREN,
	T_RPAREN,
	T_SEMI,
	T_BG
}							t_token_type;

typedef struct s_token_segment
{
	char					*content;
	t_quote_type			quote;
	bool					is_expand;
	struct s_token_segment	*next;
}							t_token_segment;

typedef struct s_token
{
	t_token_type			type;
	t_token_segment			*segments;
	struct s_token			*next;
}							t_token;

typedef enum e_lexer_state
{
	LEXER_NORMAL,
	LEXER_SINGLE_QUOTE,
	LEXER_DOUBLE_QUOTE
}							t_lexer_state;

/***********************************/
/**********    ERROR    **********/
typedef enum e_syntax_err
{
	ERR_NONE,
	ERR_BONUS,
	ERR_PIPE_AT_EDGE,
	ERR_CONSECUTIVE_PIPES,
	ERR_ISOLATED_OP,
	ERR_MISSING_FILENAME,
	ERR_UNCLOSED_QUOTE,
	ERR_LINE_CONTINUATION,
	ERR_INVALID_SEQUENCE
}							t_syntax_err;

typedef struct s_check_synt
{
	t_syntax_err	code_err;
	t_token			*token_err;
}							t_check_synt;

typedef struct s_utils_lexer
{
	t_lexer_state			state;
	int						i;
	char					c;
	t_dynamic_buffer		*buffer;
	t_quote_type			current_quote;
	bool					new_arg;
	t_syntax_err			error;
}							t_utils_lexer;
/***********************************/
/**********     PARSER    **********/
typedef struct s_redirection
{
	int						type;
	char					*target;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**args;
	t_redirection			*redirs;
	pid_t					pid;
	int						*status;
	struct s_command		*next;
}							t_command;
/***********************************/
/**********     FILENAME    **********/
typedef struct s_tempfile
{
	int						fd;
	int						counter;
	int						len;
	char					*filename;
}							t_tempfile;

typedef struct s_creat_tempfile
{
	char         *filename;
	unsigned char rnd[RANDOM_BYTES];
	char         hexpart[RANDOM_BYTES * 2 + 1];
	int          tries;
	int          fd;
}   t_creat_tempfile;
/***********************************/
/**********     EXPAND    **********/
typedef struct s_expand_vars
{
	char					*result;
	char					tmp[2];
	size_t					i;
	size_t					start;
	size_t					len;
	char					*name;
	char					*value;
	char					*buf;
}							t_expand_vars;

typedef struct s_expand_handle
{
	t_token					*current;
	t_token_segment			*seg;
	char					*old;
	bool					can_expand;
	bool					had_dollar;
}							t_expand_handle;

/***********************************/
/**********     HEREDOC    **********/
typedef struct s_heredoc
{
	char					*delimiter;
	char					*content;
	size_t					content_len;
	size_t					line_count;
}							t_heredoc;

/***********************************/
/**********    ENV    **********/
typedef struct s_env
{
	char					**env;
	int						error_code;
}							t_env;

/***********************************/
/**********    MEMORY    **********/
typedef struct s_mem_node
{
	void				*ptr;
	struct s_mem_node	*next;
}		t_mem_node;

#endif
