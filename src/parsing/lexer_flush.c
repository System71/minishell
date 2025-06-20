/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:25:01 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/02 19:16:46 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_buffer(t_utils_lexer *storage, t_token **tokens, bool mergeable)
{
	
		if (storage->buffer->len > 0
		|| (storage->state != LEXER_NORMAL && storage->current_quote != QUOTE_NONE))
	{
		storage->buffer->data[storage->buffer->len] = '\0';
		add_token_or_segment(tokens, storage->buffer->data,
			storage->current_quote, mergeable);
		storage->buffer->len = 0;
		storage->buffer->data[0] = '\0';
		storage->current_quote = QUOTE_NONE;
	}
}
