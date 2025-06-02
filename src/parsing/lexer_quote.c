/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:30:05 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/02 19:01:49 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

void	enter_quote_state(t_utils_lexer *storage, t_token **tokens,
		t_lexer_state new_state, t_quote_type new_quote)
{
	if (storage->new_arg == true)
	{
		if (storage->buffer->len > 0)
		{
			storage->new_arg = false;
		}
		flush_buffer(storage, tokens, false);
	}
	else
	{
		flush_buffer(storage, tokens, true);
	}
	storage->state = new_state;
	storage->current_quote = new_quote;
}

void	process_quote_char(t_utils_lexer *storage, t_token **tokens)
{
	if ((storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'')
			|| (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"'))
	{
		if (storage->new_arg == true && storage->buffer->len > 0)
		{
			storage->new_arg = false;
			flush_buffer(storage, tokens, false);
		}
		else
			flush_buffer(storage, tokens, true);
		storage->state = LEXER_NORMAL;
	}
	else
	{
		if (!append_char(storage->buffer, storage->c))
		{
			printf("Error: Allocation failed in append_char\n");
			exit(EXIT_FAILURE);
		}
	}
}
