/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/30 08:07:42 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/lib_utils.h"
#include <ctype.h>
#include <stdio.h>

static void	handle_space(t_utils_lexer *storage, t_token **tokens)
{
	flush_buffer(storage, tokens, false);
	storage->new_arg = true;
}

static void	handle_special_char(t_utils_lexer *storage,
								const char *input,
								t_token **tokens)
{
	char	dbl[3];
	char	single[2];

	flush_buffer(storage, tokens, false);
	if ((storage->c == '>' || storage->c == '<')
		&& input[storage->i + 1] != '\0'
		&& input[storage->i + 1] == storage->c)
	{
		dbl[0] = storage->c;
		dbl[1] = storage->c;
		dbl[2] = '\0';
		add_token_or_segment(tokens, dbl, QUOTE_NONE, false);
		storage->i++;
	}
	else
	{
		single[0] = storage->c;
		single[1] = '\0';
		add_token_or_segment(tokens, single, QUOTE_NONE, false);
	}
	storage->new_arg = false;
}

static void	handle_default_char(t_utils_lexer *storage)
{
	bool	ok;

	ok = append_char(storage->buffer, storage->c);
	if (!ok)
	{
		printf("Error: Allocation failed in append_char\n");
		exit(EXIT_FAILURE);
	}
}

void	process_normal_char(t_utils_lexer *storage,
							const char *input,
							t_token **tokens)
{
	if (isspace(storage->c))
		handle_space(storage, tokens);
	else if (storage->c == '\'')
	{
		enter_quote_state(storage,
			tokens,
			LEXER_SINGLE_QUOTE,
			QUOTE_SINGLE);
	}
	else if (storage->c == '\"')
	{
		enter_quote_state(storage,
			tokens,
			LEXER_DOUBLE_QUOTE,
			QUOTE_DOUBLE);
	}
	else if (is_special_char(storage->c))
	{
		handle_special_char(storage, input, tokens);
	}
	else
		handle_default_char(storage);
}
