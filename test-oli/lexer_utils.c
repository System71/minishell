/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:19:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 13:04:57 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

void process_normal_char(char c, const char *input, int *i, t_lexer_state *state,
                         char *buffer, int *buf_index, t_token **tokens)
{
    if (isspace(c))
        flush_buffer(buffer, buf_index, tokens);
    else if (c == '\'')
        *state = LEXER_SINGLE_QUOTE;
    else if (c == '\"')
        *state = LEXER_DOUBLE_QUOTE;
    else if (is_special_char(c))
    {
        flush_buffer(buffer, buf_index, tokens);
        // Vérifie si le caractère spécial est doublé
        if ((c == '>' || c == '<') && input[*i + 1] && input[*i + 1] == c)
        {
            char dbl[3] = { c, c, '\0' };
            *tokens = add_token(*tokens, dbl);
            (*i)++;
        }
        else
        {
            char single[2] = { c, '\0' };
            *tokens = add_token(*tokens, single);
        }
    }
    else
        buffer[(*buf_index)++] = c;
}

void process_quote_char(char c, t_lexer_state *state, char *buffer, int *buf_index)
{
    if ((*state == LEXER_SINGLE_QUOTE && c == '\'') ||
        (*state == LEXER_DOUBLE_QUOTE && c == '\"'))
    {
        *state = LEXER_NORMAL;
    }
    else
        buffer[(*buf_index)++] = c;
}

