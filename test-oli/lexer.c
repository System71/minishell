/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:46:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/14 12:59:04 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

    /* Initialisation context */
void	init_utils_lexer(t_utils_lexer *storage)
{
    storage->state = LEXER_NORMAL;
    storage->i = 0;
    storage->c = '\0';
    storage->buffer = init_dynamic_buffer();
    storage->current_quote = QUOTE_NONE;
    storage->new_arg = false;
}

t_token *lexer(const char *input)
{
	t_token *tokens = NULL;
	t_utils_lexer storage;

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
			process_quote_char(&storage, &tokens);
		}
		storage.i++;
	}
	if (storage.new_arg == true)
		flush_buffer(&storage, &tokens, false);
	else
		flush_buffer(&storage, &tokens, true);

	if (storage.state != LEXER_NORMAL)
	{
		printf("Error: unclosed quote!\n");
	}
	free_dynamic_buffer(storage.buffer);
	return tokens;
}
