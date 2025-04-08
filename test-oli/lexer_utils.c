/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/07 14:42:57 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
t_token_type get_token_type(const char *str)
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
    return T_WORD;
}
int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '$');
}

t_token *add_token(t_token **list, const char *content, t_quote_type quote)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return *list;  // Ou gérer l'erreur autrement
    new_token->type = get_token_type(content);
    new_token->content = strdup(content);
    if (!new_token->content) {
        free(new_token);
        return *list;  // Ou gérer l'erreur
    }
    new_token->quote = quote;
    new_token->next = NULL;
    
    if (!*list)
    {
        *list = new_token;
    }
    else
    {
        t_token *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
    return *list;
}
void flush_buffer(t_utils_lexer *storage, t_token **tokens)
{
    if (storage->buffer->len > 0)
    {
        // On s'assure que la chaîne est terminée
        storage->buffer->data[storage->buffer->len] = '\0';
        // Création du token à partir du contenu du buffer dynamique
        *tokens = add_token(tokens, storage->buffer->data, storage->current_quote);
        // Réinitialisation du buffer dynamique pour la prochaine accumulation
        storage->buffer->len = 0;
        storage->buffer->data[0] = '\0';
        // Réinitialiser l'état de quote
        storage->current_quote = QUOTE_NONE;
    }
}
void process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens)
{
    if (isspace(storage->c))
    {
        // Les espaces délimitent un token, on vide le buffer.
        flush_buffer(storage, tokens);
    }
    else if (storage->c == '\'')
    {
        // Avant d'entrer en mode quote, on vide le buffer pour isoler le token.
        flush_buffer(storage, tokens);
        storage->state = LEXER_SINGLE_QUOTE;
        storage->current_quote = QUOTE_SINGLE;
    }
    else if (storage->c == '\"')
    {
        flush_buffer(storage, tokens);
        storage->state = LEXER_DOUBLE_QUOTE;
        storage->current_quote = QUOTE_DOUBLE;
    }
    else if (is_special_char(storage->c))
    {
        flush_buffer(storage, tokens);
        // Vérifie si le caractère spécial est doublé (>> ou <<)
        if ((storage->c == '>' || storage->c == '<') &&
            input[storage->i + 1] != '\0' && input[storage->i + 1] == storage->c)
        {
            char dbl[3] = { storage->c, storage->c, '\0' };
            *tokens = add_token(tokens, dbl, storage->current_quote);
            storage->i++;  // On saute le caractère doublé
        }
        else
        {
            char single[2] = { storage->c, '\0' };
            *tokens = add_token(tokens, single, storage->current_quote);
        }
    }
    else
    {
        // Caractère normal : on l'ajoute au buffer dynamique.
        if (!append_char(storage->buffer, storage->c))
        {
            fprintf(stderr, "Error: Allocation failed in append_char\n");
            exit(EXIT_FAILURE);
        }
    }
}

void process_quote_char(t_utils_lexer *storage)
{
    // Vérifie si le caractère courant est la quote fermante selon l'état
    if ((storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'') ||
        (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"'))
    {
        // Fin de la séquence quote, on retourne à l'état normal.
        storage->state = LEXER_NORMAL;
    }
    else
    {
        // À l'intérieur des quotes, on accumule tous les caractères.
        if (!append_char(storage->buffer, storage->c))
        {
            fprintf(stderr, "Error: Allocation failed in append_char\n");
            exit(EXIT_FAILURE);
        }
    }
}

