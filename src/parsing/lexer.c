/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:46:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/13 19:49:50 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_utils_lexer(t_utils_lexer *storage)
{
	storage->state = LEXER_NORMAL;
	storage->i = 0;
	storage->c = '\0';
	storage->buffer = init_dynamic_buffer();
	storage->current_quote = QUOTE_NONE;
	storage->new_arg = false;
	storage->error = ERR_NONE;
}

static void	clean_last_buffer(t_token **tokens, t_utils_lexer *storage)
{
	if (storage->new_arg == true)
		flush_buffer(storage, tokens, false);
	else
		flush_buffer(storage, tokens, true);
	if (storage->state != LEXER_NORMAL && storage->error == ERR_NONE)
	{
		storage->error = ERR_UNCLOSED_QUOTE;
	}
}

t_token	*lexer(const char *input)
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
			process_quote_char(&storage, &tokens);
		}
		storage.i++;
	}
	
	clean_last_buffer(&tokens, &storage);
	if (storage.error != ERR_NONE)
	{
		report_syntax_error(storage.error, input);
		return (NULL);
	}
	return (tokens);
}
