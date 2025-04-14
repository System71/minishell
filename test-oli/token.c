/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/14 08:10:26 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

const char *token_quote_to_string(t_quote_type quote)
{
	switch (quote)
	{
		case QUOTE_NONE:	  return "None";
		case QUOTE_SINGLE:	  return "Single";
		case QUOTE_DOUBLE:	  return "Double";
	}
}

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case T_WORD:          return "Word";
        case T_REDIRECT_IN:   return "Redirect_In";
        case T_REDIRECT_OUT:  return "Redirect_Out";
        case T_APPEND:        return "Append";
        case T_HEREDOC:       return "Heredoc";
        case T_PIPE:          return "Pipe";
        case T_DOLLAR:        return "Dollar";

        default:              return "UNKNOWN";
    }
}


/* Fonction de débogage : affiche la liste des tokens et leurs segments */
void print_tokens(t_token *tokens)
{
    int token_num = 1;
    while (tokens)
    {
		printf("----------------------------------------------------------------------\n");
        printf("Token %d: Type: %s\n", token_num, token_type_to_string(tokens->type));
        t_token_segment *seg = tokens->segments;
        int seg_num = 1;
        while (seg)
        {
            printf("  Segment %d| Quote: %s, Content: \"%s\"\n",
                   seg_num, token_quote_to_string(seg->quote), seg->content);
            seg = seg->next;
            seg_num++;
        }
		printf("----------------------------------------------------------------------\n");
        tokens = tokens->next;
        token_num++;
    }
}
