/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:20:22 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 13:04:34 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

/*
** Implémentation du lexer
**
** Le lexer parcourt l'entrée caractère par caractère en gérant trois états :
** NORMAL, SINGLE_QUOTE et DOUBLE_QUOTE. Le contenu est stocké dans un buffer
** et "flusher" dès qu'un séparateur (espace ou caractère spécial) est rencontré.
*/
t_token *lexer(const char *input)
{
    t_token *tokens = create_empty_token_list();
    t_lexer_state state = LEXER_NORMAL;
    char buffer[BUFFER_SIZE];
    int buf_index = 0;
    
    memset(buffer, 0, BUFFER_SIZE);
    
    for (int i = 0; input[i] != '\0'; i++)
    {
        char c = input[i];
        
        if (state == LEXER_NORMAL)
        {
            if (isspace(c))
            {
                flush_buffer(buffer, &buf_index, &tokens);
            }
            else if (c == '\'')
            {
                state = LEXER_SINGLE_QUOTE;
            }
            else if (c == '\"')
            {
                state = LEXER_DOUBLE_QUOTE;
            }
            else if (is_special_char(c))
            {
                flush_buffer(buffer, &buf_index, &tokens);
                // Vérifie si le caractère spécial peut être doublé (>> ou <<)
                if ((c == '>' || c == '<') && input[i + 1] != '\0' && input[i + 1] == c)
                {
                    char dbl[3] = { c, c, '\0' };
                    tokens = add_token(tokens, dbl);
                    i++; // On saute le prochain caractère.
                }
                else
                {
                    char single[2] = { c, '\0' };
                    tokens = add_token(tokens, single);
                }
            }
            else
            {
                buffer[buf_index++] = c;
            }
        }
        else if (state == LEXER_SINGLE_QUOTE)
        {
            if (c == '\'')
                state = LEXER_NORMAL;
            else
                buffer[buf_index++] = c;
        }
        else if (state == LEXER_DOUBLE_QUOTE)
        {
            if (c == '\"')
                state = LEXER_NORMAL;
            else
                buffer[buf_index++] = c;
        }
    }
    flush_buffer(buffer, &buf_index, &tokens);
    return tokens;
}
