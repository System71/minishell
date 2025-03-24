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
    // Mettez ici ce qui vous est utile (arguments, redirections, etc.)
    char    *dummy;
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
    new_token->type = T_WORD; // simplifié : à adapter selon le contenu
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
t_command *create_new_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->dummy = NULL; // initialisation
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

    // On s'assure de vider le buffer
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
                    // On ajoute le buffer comme token
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
                // On vide d’abord le buffer si nécessaire
                if (buf_index > 0)
                {
                    buffer[buf_index] = '\0';
                    tokens = add_token(tokens, buffer);
                    buf_index = 0;
                    memset(buffer, 0, BUFFER_SIZE);
                }
                // Puis on ajoute le caractère spécial comme token
                char tmp[2] = { c, '\0' };
                tokens = add_token(tokens, tmp);
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
    // Fin de la boucle : s’il reste un buffer non vide, on l’ajoute
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
t_command *parser(t_token *tokens)
{
    (void)tokens; // on n'utilise pas encore tokens
    t_command *cmd = create_new_command();
    return cmd;
}

/*
** 8) Main de test
*/
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
        printf("Type: %d, Contenu: %s\n", tmp->type, tmp->content);
        tmp = tmp->next;
    }

    // Parser (exemple très basique)
    t_command *cmd = parser(tokens);
    if (cmd)
        printf("Structure de commande créée avec succès (exemple).\n");

    // Ici, vous ajouteriez vos free_tokens(), free_command(), etc.
    // ...

    return EXIT_SUCCESS;
}

