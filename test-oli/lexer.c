/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:46:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/03 14:52:27 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

// Gerer les $ en envoyer string, ou var_env;
void	init_utils_lexer(t_utils_lexer *storage)
{
	storage->state = LEXER_NORMAL;
	storage->buf_index = 0;
    storage->buffer = init_dynamic_buffer();
	storage->i = 0;
    storage->current_quote = QUOTE_NONE;

}

t_token *lexer(const char *input)
{
    t_token			*tokens;
	t_utils_lexer	storage;

	tokens = NULL;
	init_utils_lexer(&storage);
     while (input[storage.i] != '\0')
    {
        storage.c = input[storage.i];
        
        if (storage.state == LEXER_NORMAL)
        {
			process_normal_char(&storage, input, &tokens);
        }
        else
		{
			process_quote_char(&storage);
        }
		storage.i++;
    }
    flush_buffer(&storage, &tokens);
	if (storage.state != LEXER_NORMAL)
	{
		printf("Error quote ! \n");
	}
    return tokens;
}
