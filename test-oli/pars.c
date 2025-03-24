#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/*
** 1) On déclare l’énumération pour l’état du lexer
*/
typedef enum e_lexer_state
{
    LEXER_NORMAL,
    LEXER_SINGLE_QUOTE,
    LEXER_DOUBLE_QUOTE
}   t_lexer_state;

/*
** 2) Définition des types de tokens
*/
typedef enum e_token_type
{
    T_WORD,          // mot ou chaîne de caractères classique
    T_SINGLE_QUOTE,  // token provenant de quotes simples
    T_DOUBLE_QUOTE,  // token provenant de double quotes
    T_REDIRECT_IN,   // token pour '<'
    T_REDIRECT_OUT,  // token pour '>'
    T_APPEND,        // token pour '>>'
    T_HEREDOC,       // token pour '<<'
    T_PIPE,          // token pour '|'
    T_AND,           // token pour '&&' (bonus)
    T_OR,            // token pour '||' (bonus)
    T_DOLLAR,        // token pour '$'
    T_BACKSLASH,     // token pour '\'
    T_OPEN_PAREN,    // token pour '('
    T_CLOSE_PAREN,   // token pour ')'
    T_SEMICOLON,     // token pour ';'
    // etc.
}   t_token_type;

static t_token_type get_token_type(const char *str)
{
    if (strcmp(str, "|") == 0)
        return T_PIPE;
    else if (strcmp(str, "<") == 0)
        return T_REDIRECT_IN;
    else if (strcmp(str, ">") == 0)
        return T_REDIRECT_OUT;
    else if (strcmp(str, ">>") == 0)
        return T_APPEND;
    else if (strcmp(str, "<<") == 0)
        return T_HEREDOC;
    else if (strcmp(str, "&&") == 0)
        return T_AND;
    else if (strcmp(str, "||") == 0)
        return T_OR;
    else if (strcmp(str, "(") == 0)
        return T_OPEN_PAREN;
    else if (strcmp(str, ")") == 0)
        return T_CLOSE_PAREN;
    else if (strcmp(str, ";") == 0)
        return T_SEMICOLON;
    // etc. Ajoutez d’autres règles si nécessaire
    // Sinon, c’est un mot (par défaut).
    return T_WORD;
}

/*
** 3) Structure du token (liste chaînée)
*/
typedef struct s_token
{
    t_token_type    type;     
    char            *content; 
    struct s_token  *next;
}   t_token;

/*
** 4) Structure de commande (exemple minimal)
*/

typedef struct s_command
{
    char    **argv;        // Tableau dynamique d'arguments (terminé par NULL)
    int     argc;          // Nombre d'arguments
    struct s_command *next; // Pour chaîner les commandes en cas de pipeline
}   t_command;

/*
** 5) Fonctions minimales à implémenter ou "stubber"
**    - create_empty_token_list
**    - add_token
**    - is_special_char
**    - create_new_command
*/

/* Crée une liste vide (ici on renvoie juste NULL) */
t_token *create_empty_token_list(void)
{
    return NULL;
}

/* Vérifie si c est un caractère spécial (à adapter à vos besoins) */
int is_special_char(char c)
{
    // Ex. on considère | < > & ( ) $ ; comme spéciaux
    return (c == '|' || c == '<' || c == '>' || c == '&' 
            || c == '(' || c == ')' || c == '$' || c == ';');
}

/*
** Ajoute un token en fin de liste (exemple très simple)
** Ici, on ne détermine pas le type, on stocke toujours T_WORD.
** Adaptez la logique pour gérer les différents types (T_PIPE, T_REDIRECT_IN, etc.)
*/
t_token *add_token(t_token *list, const char *content)
{
    t_token *new_token = malloc(sizeof(t_token));
    t_token *tmp;

    if (!new_token)
        return list; // ou NULL si vous préférez
    new_token->type = get_token_type(content); // simplifié : à adapter selon le contenu
    new_token->content = strdup(content); // duplique la chaîne
    new_token->next = NULL;

    if (!list)
        return new_token;
    tmp = list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_token;
    return list;
}

/* Crée une nouvelle structure de commande */
t_command *create_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->argc = 0;
    cmd->argv = NULL;
    cmd->next = NULL;
    return cmd;
}

/*
** 6) Implémentation de votre lexer
**    On remplace "State current_state = NORMAL;" par l’énum déclarée : t_lexer_state current_state = LEXER_NORMAL;
*/
t_token *lexer(const char *input)
{
    t_token         *tokens = create_empty_token_list();
    t_lexer_state   current_state = LEXER_NORMAL;
    char            buffer[BUFFER_SIZE];
    int             buf_index = 0;
    int             i;
    
    memset(buffer, 0, BUFFER_SIZE);

    for (i = 0; input[i] != '\0'; i++)
    {
        char c = input[i];

        if (current_state == LEXER_NORMAL)
        {
            if (c == ' ')
            {
                if (buf_index > 0)
                {
                    buffer[buf_index] = '\0';
                    tokens = add_token(tokens, buffer);
                    buf_index = 0;
                    memset(buffer, 0, BUFFER_SIZE);
                }
            }
            else if (c == '\'')
            {
                current_state = LEXER_SINGLE_QUOTE;
            }
            else if (c == '\"')
            {
                current_state = LEXER_DOUBLE_QUOTE;
            }
            else if (is_special_char(c))
            {
                if (buf_index > 0)
                {
                    buffer[buf_index] = '\0';
                    tokens = add_token(tokens, buffer);
                    buf_index = 0;
                    memset(buffer, 0, BUFFER_SIZE);
                }
                // Vérifier si le caractère spécial peut être doublé
                if ((c == '>' || c == '<' || c == '|' || c == '&') && input[i + 1] != '\0' && input[i + 1] == c)
                {
                    char tmp[3] = { c, c, '\0' };
                    tokens = add_token(tokens, tmp);
                    i++; // On saute le caractère suivant déjà traité
                }
                else
                {
                    char tmp[2] = { c, '\0' };
                    tokens = add_token(tokens, tmp);
                }
            }
            else
            {
                buffer[buf_index++] = c;
            }
        }
        else if (current_state == LEXER_SINGLE_QUOTE)
        {
            if (c == '\'')
                current_state = LEXER_NORMAL;
            else
                buffer[buf_index++] = c;
        }
        else if (current_state == LEXER_DOUBLE_QUOTE)
        {
            if (c == '\"')
                current_state = LEXER_NORMAL;
            else
                buffer[buf_index++] = c;
        }
    }
    if (buf_index > 0)
    {
        buffer[buf_index] = '\0';
        tokens = add_token(tokens, buffer);
    }
    return tokens;
}

/*
** 7) Implémentation d’un parser minimal
*/

// Ajoute un argument à la commande (agrandit le tableau argv)
void add_argument(t_command *cmd, const char *arg)
{
    char **new_argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
    if (!new_argv)
        return; // Gérer l'erreur en cas de besoin
    cmd->argv = new_argv;
    cmd->argv[cmd->argc] = strdup(arg); // Duplique l'argument
    cmd->argc++;
    cmd->argv[cmd->argc] = NULL; // Assure la terminaison par NULL
}

t_command *parser(t_token *tokens)
{
    t_command *head = NULL;
    t_command *current_cmd = NULL;

    while (tokens)
    {
        // Si la commande n'a pas encore été créée, en créer une nouvelle
        if (!head)
        {
            head = create_command();
            current_cmd = head;
        }
        
        // Selon le type de token, agir en conséquence
        if (tokens->type == T_WORD ||
            tokens->type == T_SINGLE_QUOTE ||
            tokens->type == T_DOUBLE_QUOTE)
        {
            // Ajouter le token comme argument de la commande en cours
            add_argument(current_cmd, tokens->content);
        }
        else if (tokens->type == T_PIPE)
        {
            // Un PIPE indique la fin de la commande en cours et le début d'une nouvelle commande
            current_cmd->next = create_command();
            current_cmd = current_cmd->next;
        }
        // Ici, vous pouvez ajouter la gestion d'autres tokens comme redirections,
        // T_REDIRECT_IN, T_REDIRECT_OUT, etc.
        
        tokens = tokens->next;
    }
    return head;
}

/*
** 8) Main de test
*/

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case T_WORD:          return "T_WORD";
        case T_SINGLE_QUOTE:  return "T_SINGLE_QUOTE";
        case T_DOUBLE_QUOTE:  return "T_DOUBLE_QUOTE";
        case T_REDIRECT_IN:   return "T_REDIRECT_IN";
        case T_REDIRECT_OUT:  return "T_REDIRECT_OUT";
        case T_APPEND:        return "T_APPEND";
        case T_HEREDOC:       return "T_HEREDOC";
        case T_PIPE:          return "T_PIPE";
        case T_AND:           return "T_AND";
        case T_OR:            return "T_OR";
        case T_DOLLAR:        return "T_DOLLAR";
        case T_BACKSLASH:     return "T_BACKSLASH";
        case T_OPEN_PAREN:    return "T_OPEN_PAREN";
        case T_CLOSE_PAREN:   return "T_CLOSE_PAREN";
        case T_SEMICOLON:     return "T_SEMICOLON";
        default:              return "UNKNOWN";
    }
}
int main(void)
{
	char    input[BUFFER_SIZE];
	t_token *tokens = NULL;
	t_token *tmp = NULL;

	printf("minishell> ");
	if (!fgets(input, BUFFER_SIZE, stdin))
	{
		printf("Erreur de lecture de l'entrée.\n");
		return EXIT_FAILURE;
	}
	// Retirer le \n éventuel
	input[strcspn(input, "\n")] = '\0';

	// Lexer
	tokens = lexer(input);
	if (!tokens)
	{
		printf("Aucun token généré.\n");
		return EXIT_FAILURE;
	}

	// Affichage des tokens
	printf("Liste des tokens générés:\n");
	tmp = tokens;
	while (tmp)
	{
		printf("Type: %d (%s), Contenu: %s\n",
		 tmp->type,
		 token_type_to_string(tmp->type),
		 tmp->content);
		tmp = tmp->next;
	}

    // Parser
    t_command *cmd_list = parser(tokens);
    if (cmd_list)
    {
        // Affichage des commandes pour vérification
        t_command *cmd = cmd_list;
        int cmd_index = 1;
        while (cmd)
        {
            printf("Commande %d:\n", cmd_index);
            for (int i = 0; i < cmd->argc; i++)
            {
                printf("  argv[%d] = %s\n", i, cmd->argv[i]);
            }
            cmd = cmd->next;
            cmd_index++;
        }
    }

	// Ici, vous ajouteriez vos free_tokens(), free_command(), etc.
	// ...

	return EXIT_SUCCESS;
}

