/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_on_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:17:19 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/30 11:17:19 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include 

bool check_syntax(t_token *tok)
{
    t_token_type	prev;

    // s'il n'y a pas de token, pas d'erreur
    if (!tok) return true;

    // Interdire un pipe en tête
    if (tok->type == T_PIPE)
    {
        fprintf(stderr, "minishell: syntax error near unexpected token '|'\n");
        return false;
    }

    while (tok)
    {
        if (tok->type == T_PIPE)
        {
            // pipe en fin ou pipe après un autre pipe
            if (!tok->next || tok->next->type == T_PIPE)
            {
                fprintf(stderr,
                    "minishell: syntax error near unexpected token '%s'\n",
                    (tok->next && tok->next->type==T_PIPE) ? "||" : "|");
                return false;
            }
        }
        else if (is_redirection_type(tok->type))
        {
            // redirection sans mot qui suit
            if (!tok->next || tok->next->type != T_WORD)
            {
                fprintf(stderr,
                    "minishell: syntax error near unexpected token '%s'\n",
                    tok->type == T_HEREDOC ? "<<" :
                    tok->type == T_REDIRECT_IN ? "<" : ">");
                return false;
            }
        }
        prev = tok->type;
        tok = tok->next;
    }

    // Interdire un pipe en fin
    if (prev == T_PIPE)
    {
        fprintf(stderr, "minishell: syntax error near unexpected token 'newline'\n");
        return false;
    }
    return true;
}

