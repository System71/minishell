/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:02:29 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parsing_utils.h"
#include <stdio.h>

static void	handle_space(t_utils_lexer *storage, t_token **tokens)
{
	flush_buffer(storage, tokens, false);
	storage->new_arg = true;
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

static size_t	get_operator(const char *input, size_t i, char *op)
{
	size_t	len;
	char	c;

	c = input[i];
	if ((c == '|' || c == '&' || c == '<' || c == '>')
		&& input[i + 1] == c)
	{
		op[0] = c;
		op[1] = c;
		op[2] = '\0';
		len = 2;
	}
	else
	{
		op[0] = c;
		op[1] = '\0';
		len = 1;
	}
	return (len);
}

static void	handle_special_char(t_utils_lexer *storage,
								const char *input,
								t_token **tokens)
{
	char	op[3];
	size_t	len;

	flush_buffer(storage, tokens, false);
	len = get_operator(input, storage->i, op);
	add_token_or_segment(tokens, op, QUOTE_NONE, false);
	storage->i += (len - 1);
	storage->new_arg = false;
}

void	process_normal_char(t_utils_lexer *storage,
					const char *input, t_token **tokens)
{
	if (ft_iswhitespace(storage->c))
		handle_space(storage, tokens);
	else if (storage->c == '\'')
		enter_quote_state(storage, tokens, LEXER_SINGLE_QUOTE, QUOTE_SINGLE);
	else if (storage->c == '\"')
		enter_quote_state(storage, tokens, LEXER_DOUBLE_QUOTE, QUOTE_DOUBLE);
	else if (is_special_char(storage->c))
		handle_special_char(storage, input, tokens);
	else
		handle_default_char(storage);
}
