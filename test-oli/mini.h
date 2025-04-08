#ifndef MINI_H
#define MINI_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

// COMMANDE
typedef struct s_command
{
    t_token_type     type;
	char           **argv;
    int              argc;
	t_quote_type	quote;
    struct s_command *next;
} t_command;

// Fonctions pour gérer la création et la manipulation de commandes
t_command *create_command(void);
void       add_argument(t_command *cmd, t_token *token, t_token_type type);
void       print_commands(t_command *cmd_list);
const char *token_quote_to_string(t_quote_type quote);

// PARSER
t_command *parser(t_token *tokens);


#endif
