/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:27:55 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/25 12:31:40 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"
#include "../../includes/lib_utils.h"

t_token_segment *create_segment(const char *content, t_quote_type quote)
{
    t_token_segment *seg = malloc(sizeof(t_token_segment));
    if (!seg)
        return NULL;
    seg->content = ft_strdup(content);
    if (!seg->content) {
        free(seg);
        return NULL;
    }
    seg->quote = quote;
    seg->next = NULL;
    return seg;
}

void add_segment_to_token(t_token *token, const char *content, t_quote_type quote)
{
    t_token_segment *new_seg = create_segment(content, quote);
    if (!new_seg)
        return; // Gérer l'erreur
    if (!token->segments)
    {
        token->segments = new_seg;
    }
    else
    {
        t_token_segment *tmp = token->segments;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_seg;
    }
}
