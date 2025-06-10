/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/02 19:16:48 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

static void	append_new_token(t_token **tokens,
							const char *content,
							t_quote_type quote)
{
	t_token	*new_token;

	new_token = create_token_with_segment(content, quote);
	if (!new_token)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
		get_last_token(*tokens)->next = new_token;
}

static void	add_or_append_segment(t_token **tokens,
								const char *content,
								t_quote_type quote)
{
	t_token	*last;

	last = get_last_token(*tokens);
	if (last && last->type == T_WORD)
	{
		add_segment_to_token(last, content, quote);
	}
	else
	{
		append_new_token(tokens, content, quote);
	}
}

void	add_token_or_segment(t_token **tokens,
						const char *content,
						t_quote_type quote,
						bool mergeable)
{
	if (!*tokens || !mergeable)
		append_new_token(tokens, content, quote);
	else
		add_or_append_segment(tokens, content, quote);
}
