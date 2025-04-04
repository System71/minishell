/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/03 18:11:58 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens)
{

            if (isspace(storage->c))
            {
                flush_buffer(storage, tokens);
            }
            else if (storage->c == '\'')
            {
                storage->state = LEXER_SINGLE_QUOTE;
				storage->spl_quote_open = true;
            }
            else if (storage->c == '\"')
            {
                storage->state = LEXER_DOUBLE_QUOTE;
				storage->dbl_quote_open = true;
            }
            else if (is_special_char(storage->c))
            {
                flush_buffer(storage, tokens);
                // Vérifie si le caractère spécial peut être doublé (>> ou <<)
                if ((storage->c == '>' || storage->c == '<') &&
					input[storage->i + 1] != '\0' && input[storage->i + 1] == storage->c)
                {
                    char dbl[3] = { storage->c, storage->c, '\0' };
                    *tokens = add_token(*tokens, dbl);
                    storage->i++; // On saute le prochain caractère.
                }
                else
                {
                    char single[2] = { storage->c, '\0' };
                    *tokens = add_token(*tokens, single);
                }
            }
            else
            {
                storage->buffer[storage->buf_index++] = storage->c;
            }

}

void process_quote_char(t_utils_lexer *storage)
{
    if (storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'')
    {
		if (storage->spl_quote_open == true)
        	storage->state = LEXER_NORMAL;
    }
	else	if (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"')
	{
		if (storage->dbl_quote_open == true)
        	storage->state = LEXER_NORMAL;
	}
    else
        storage->buffer[(storage->buf_index)++] = storage->c;
}

