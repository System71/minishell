/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/08 13:44:14 by okientzl         ###   ########.fr       */
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

t_token *add_token(t_token **list, const char *content, t_quote_type quote, bool mergeable)
{
    t_token	*new_token;

	new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);  // Warning error manage
    new_token->type = get_token_type(content);
    new_token->content = strdup(content); // ft_strdup replace
    if (!new_token->content)
	{
        free(new_token);
        return (NULL);   // Warning error manage
    }
    new_token->quote = quote;
    new_token->mergeable = mergeable;
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

void flush_buffer(t_utils_lexer *storage, t_token **tokens, bool mergeable)
{
    if (storage->buffer->len > 0)
    {
        storage->buffer->data[storage->buffer->len] = '\0';
        *tokens = add_token(tokens, storage->buffer->data, storage->current_quote, mergeable);
        // Réinitialisation du buffer dynamique pour la prochaine accumulation
        storage->buffer->len = 0;
        storage->buffer->data[0] = '\0';
        // Remise à zéro du flag de quote
        storage->current_quote = QUOTE_NONE;
    }
}

void process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens)
{
    if (isspace(storage->c))
    {
        // Espace : fin de token, on ne fusionnera pas avec le suivant
        flush_buffer(storage, tokens, false);
    }
    else if (storage->c == '\'')
    {
        // Lorsque vous rencontrez une quote, vous souhaitez isoler la partie qui précède
        // sans séparation par espace : on indique que le token précédent est fusionnable
        flush_buffer(storage, tokens, true);
        storage->state = LEXER_SINGLE_QUOTE;
        storage->current_quote = QUOTE_SINGLE;
    }
    else if (storage->c == '\"')
    {
        flush_buffer(storage, tokens, true);
        storage->state = LEXER_DOUBLE_QUOTE;
        storage->current_quote = QUOTE_DOUBLE;
    }
    else if (is_special_char(storage->c))
    {
        // Pour les caractères spéciaux, on force la création d’un token distinct.
        flush_buffer(storage, tokens, false);
        // Gère le cas doublé (>> ou <<)
        if ((storage->c == '>' || storage->c == '<') &&
            input[storage->i + 1] != '\0' && input[storage->i + 1] == storage->c)
        {
            char dbl[3] = { storage->c, storage->c, '\0' };
            *tokens = add_token(tokens, dbl, storage->current_quote, false);
            storage->i++;  // On saute le caractère doublé
        }
        else
        {
            char single[2] = { storage->c, '\0' };
            *tokens = add_token(tokens, single, storage->current_quote, false);
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
    // Lorsque l'on rencontre la quote fermante, on finit la séquence, mais on indique qu'elle doit être fusionnée
    if ((storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'') ||
        (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"'))
    {
        storage->state = LEXER_NORMAL;
    }
    else
    {
        if (!append_char(storage->buffer, storage->c))
        {
            fprintf(stderr, "Error: Allocation failed in append_char\n");
            exit(EXIT_FAILURE);
        }
    }
}
