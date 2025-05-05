/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_synthaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/05 12:51:45 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"

const char *syntax_err_msg(t_syntax_err err)
{
    switch (err)
    {
        case ERR_BONUS:
            return "We don't make a Bonus";
        case ERR_PIPE_AT_EDGE:
        case ERR_CONSECUTIVE_PIPES:
            return "syntax error near unexpected token `|`";
        case ERR_ISOLATED_OP:
            return "syntax error: isolated control operator";
        case ERR_MISSING_FILENAME:
            return "syntax error: missing name for redirect";
        case ERR_INVALID_SEQUENCE:
            return "syntax error near invalid token sequence";
        default:
            return NULL;
    }
}

t_syntax_err verify_token_sequence(t_token *tokens)
{
    t_token *prev = NULL;
    t_token *cur  = tokens;

    while (cur)
    {
        // ── 0) Refuser tout bonus : ||, &&, ( ou ) ──────────────────────────
        if (cur->type == T_OR   ||  // '||'
            cur->type == T_AND  ||  // '&&'
            cur->type == T_LPAREN || // '(' si vous avez défini ce type
            cur->type == T_RPAREN)   // ')'
        {
            return ERR_BONUS;
        }

        // ── 1) Pipes en bord ou consécutifs ───────────────────────────────
        if (cur->type == T_PIPE)
        {
            if (prev == NULL || cur->next == NULL)
                return ERR_PIPE_AT_EDGE;
            if (prev->type == T_PIPE)
                return ERR_CONSECUTIVE_PIPES;
        }

        // ── 2) Opérateurs de contrôle isolés (;, & sans suite, etc.) ──────
        if (cur->type == T_SEMI || cur->type == T_BG)
        {
            if (prev == NULL || cur->next == NULL)
                return ERR_ISOLATED_OP;
        }

        // ── 3) Redirections sans mot suivant (<, >, >>, <<) ──────────────
        if (cur->type == T_REDIRECT_IN   ||
            cur->type == T_HEREDOC    ||
            cur->type == T_REDIRECT_OUT  ||
            cur->type == T_APPEND)
        {
            if (cur->next == NULL || cur->next->type != T_WORD)
                return ERR_MISSING_FILENAME;
        }

        // ── 4) Séquences interdites de deux tokens ─────────────────────────
        if (prev)
        {
            if ((prev->type == T_REDIRECT_OUT && cur->type == T_REDIRECT_IN) ||
                (prev->type == T_REDIRECT_IN  && cur->type == T_REDIRECT_OUT) ||
                (prev->type == T_APPEND    && cur->type == T_AND))
            {
                return ERR_INVALID_SEQUENCE;
            }
        }

        prev = cur;
        cur  = cur->next;
    }

    return ERR_NONE;
}

const char *check_syntax(t_token *tokens)
{
    if (!tokens)
        return "syntax error: lexer failure";

    t_syntax_err err = verify_token_sequence(tokens);
    if (err != ERR_NONE)
        return syntax_err_msg(err);

    return NULL;
}
