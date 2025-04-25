/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:22:45 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/25 12:34:29 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"

t_token	*create_token_with_segment(const char *content, t_quote_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (quote == QUOTE_NONE)
		token->type = get_token_type(content);
	else
		token->type = T_WORD;
    token->segments = create_segment(content, quote);
    token->next = NULL;
    return (token);
}
