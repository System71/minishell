/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_synthaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 12:24:30 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include "../../includes/lexer.h"

bool is_bonus_token(t_token *cur)
{
    return cur->type == T_OR
        || cur->type == T_AND
        || cur->type == T_LPAREN
        || cur->type == T_RPAREN;
}

bool is_pipe_at_edge(t_token *prev, t_token *cur)
{
    return cur->type == T_PIPE
        && (prev == NULL || cur->next == NULL);
}

bool is_consecutive_pipes(t_token *prev, t_token *cur)
{
    return cur->type == T_PIPE
        && prev != NULL
        && prev->type == T_PIPE;
}

bool is_isolated_op(t_token *prev, t_token *cur)
{
    // ; ou &
    return (cur->type == T_SEMI || cur->type == T_BG)
        && (prev == NULL || cur->next == NULL);
}

bool is_redirect_without_word(t_token *cur)
{
    if (cur->type == T_REDIRECT_IN
     || cur->type == T_HEREDOC
     || cur->type == T_REDIRECT_OUT
     || cur->type == T_APPEND)
    {
        return cur->next == NULL
            || cur->next->type != T_WORD;
    }
    return false;
}

bool is_invalid_sequence(t_token *prev, t_token *cur)
{
    if (!prev)
        return false;
    // ><, <>, >>&, …
    if (prev->type == T_REDIRECT_OUT && cur->type == T_REDIRECT_IN)
        return true;
    if (prev->type == T_REDIRECT_IN  && cur->type == T_REDIRECT_OUT)
        return true;
    if (prev->type == T_APPEND        && cur->type == T_AND)
        return true;
    return false;
}

t_syntax_err verify_token_sequence(t_token *tokens)
{
    t_token *prev = NULL;
    t_token *cur  = tokens;

    while (cur)
    {
        if (is_bonus_token(cur))
            return ERR_BONUS;
        if (is_pipe_at_edge(prev, cur))
            return ERR_PIPE_AT_EDGE;
        if (is_consecutive_pipes(prev, cur))
            return ERR_CONSECUTIVE_PIPES;
        if (is_isolated_op(prev, cur))
            return ERR_ISOLATED_OP;
        if (is_redirect_without_word(cur))
            return ERR_MISSING_FILENAME;
        if (is_invalid_sequence(prev, cur))
            return ERR_INVALID_SEQUENCE;
        prev = cur;
        cur  = cur->next;
    }

    return ERR_NONE;
}

/*t_syntax_err verify_token_sequence(t_token *tokens)*/
/*{*/
/*    t_token *prev = NULL;*/
/*    t_token *cur  = tokens;*/
/**/
/*    while (cur)*/
/*    {*/
/*        // ── 0) Refuser tout bonus : ||, &&, ( ou ) ──────────────────────────*/
/*        if (cur->type == T_OR   ||  // '||'*/
/*            cur->type == T_AND  ||  // '&&'*/
/*            cur->type == T_LPAREN || // '(' si vous avez défini ce type*/
/*            cur->type == T_RPAREN)   // ')'*/
/*        {*/
/*            return (ERR_BONUS);*/
/*        }*/
/**/
/*        // ── 1) Pipes en bord ou consécutifs ───────────────────────────────*/
/*        if (cur->type == T_PIPE)*/
/*        {*/
/*            if (prev == NULL || cur->next == NULL)*/
/*                return (ERR_PIPE_AT_EDGE);*/
/*            if (prev->type == T_PIPE)*/
/*                return (ERR_CONSECUTIVE_PIPES);*/
/*        }*/
/**/
/*        // ── 2) Opérateurs de contrôle isolés (;, & sans suite, etc.) ──────*/
/*        if (cur->type == T_SEMI || cur->type == T_BG)*/
/*        {*/
/*            if (prev == NULL || cur->next == NULL)*/
/*                return (ERR_ISOLATED_OP);*/
/*        }*/
/**/
/*        // ── 3) Redirections sans mot suivant (<, >, >>, <<) ──────────────*/
/*        if (cur->type == T_REDIRECT_IN   ||*/
/*            cur->type == T_HEREDOC    ||*/
/*            cur->type == T_REDIRECT_OUT  ||*/
/*            cur->type == T_APPEND)*/
/*        {*/
/*            if (cur->next == NULL || cur->next->type != T_WORD)*/
/*                return (ERR_MISSING_FILENAME);*/
/*        }*/
/**/
/*        // ── 4) Séquences interdites de deux tokens ─────────────────────────*/
/*        if (prev)*/
/*        {*/
/*            if ((prev->type == T_REDIRECT_OUT && cur->type == T_REDIRECT_IN) ||*/
/*                (prev->type == T_REDIRECT_IN  && cur->type == T_REDIRECT_OUT) ||*/
/*                (prev->type == T_APPEND    && cur->type == T_AND))*/
/*            {*/
/*                return (ERR_INVALID_SEQUENCE);*/
/*            }*/
/*        }*/
/**/
/*        prev = cur;*/
/*        cur  = cur->next;*/
/*    }*/
/**/
/*    return (ERR_NONE);*/
/*}*/

bool	check_syntax(t_token *tokens)
{
	t_syntax_err	err;

	err = verify_token_sequence(tokens);
    if (err != ERR_NONE)
	{
		report_syntax_error(err, tokens->segments->content);
        return (false);
	}
    return (true);
}
