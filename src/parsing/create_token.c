/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:22:45 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 11:34:30 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"
#include "../../includes/lib_utils.h"
#include "../memory/mem.h"

char	*concat_segments(t_token *token)
{
	size_t			total_len;
	t_token_segment	*seg;
	char			*result;

	total_len = 0;
	seg = token->segments;
	while (seg)
	{
		total_len += ft_strlen(seg->content);
		seg = seg->next;
	}
	result = ft_xmalloc(total_len + 1);
	result[0] = '\0';
	seg = token->segments;
	while (seg)
	{
		ft_strcat(result, seg->content);
		seg = seg->next;
	}
	return (result);
}

t_token_segment	*create_segment(const char *content, t_quote_type quote)
{
	t_token_segment	*seg;

	seg = ft_xmalloc(sizeof(t_token_segment));
	seg->content = ft_strdup(content);
	seg->quote = quote;
	seg->next = NULL;
	return (seg);
}

void	add_segment_to_token(t_token *token,
							const char *content,
							t_quote_type quote)
{
	t_token_segment	*new_seg;
	t_token_segment	*tmp;

	new_seg = create_segment(content, quote);
	if (!token->segments)
	{
		token->segments = new_seg;
	}
	else
	{
		tmp = token->segments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_seg;
	}
}
void	rebuild_segments(t_token *tok, const char *word)
{
	tok->segments = NULL;
	add_segment_to_token(tok, word, QUOTE_NONE);
}

t_token	*create_token_with_segment(const char *content, t_quote_type quote)
{
	t_token	*token;

	token = ft_xmalloc(sizeof(t_token));
	if (quote == QUOTE_NONE)
		token->type = get_token_type(content);
	else
		token->type = T_WORD;
	token->segments = create_segment(content, quote);
	token->next = NULL;
	return (token);
}
