/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/11 13:44:18 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

const char *token_quote_to_string(t_quote_type quote)
{
	switch (quote)
	{
		case QUOTE_NONE:	  return "QUOTE_NONE";
		case QUOTE_SINGLE:	  return "QUOTE_SINGLE";
		case QUOTE_DOUBLE:	  return "QUOTE_DOUBLE";
	}
}

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case T_WORD:          return "T_WORD";
        case T_REDIRECT_IN:   return "T_REDIRECT_IN";
        case T_REDIRECT_OUT:  return "T_REDIRECT_OUT";
        case T_APPEND:        return "T_APPEND";
        case T_HEREDOC:       return "T_HEREDOC";
        case T_PIPE:          return "T_PIPE";
        case T_DOLLAR:        return "T_DOLLAR";

        default:              return "UNKNOWN";
    }
}


/* Fonction de débogage : affiche la liste des tokens et leurs segments */
void print_tokens(t_token *tokens)
{
    int token_num = 1;
    while (tokens)
    {
        printf("Token %d: Type: %d\n", token_num, tokens->type);
        t_token_segment *seg = tokens->segments;
        int seg_num = 1;
        while (seg)
        {
            printf("  Segment %d: Quote: %d, Content: \"%s\"\n",
                   seg_num, seg->quote, seg->content);
            seg = seg->next;
            seg_num++;
        }
        tokens = tokens->next;
        token_num++;
    }
}
