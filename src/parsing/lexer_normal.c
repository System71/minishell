/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:02:29 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parsing_utils.h"
#include <stdio.h>

static void	handle_space(t_utils_lexer *storage, t_token **tokens)
{
	flush_buffer(storage, tokens, false);
	storage->new_arg = true;
}

static void	handle_default_char(t_utils_lexer *storage)
{
	bool	ok;

	ok = append_char(storage->buffer, storage->c);
	if (!ok)
	{
		printf("Error: Allocation failed in append_char\n");
		exit(EXIT_FAILURE);
	}
}

static size_t get_operator(const char *input, size_t i, char *op)
{
    if (input[i] == '|' && input[i + 1] == '|')
    {
        op[0] = '|'; op[1] = '|'; op[2] = '\0';
        return (2);
    }
    if (input[i] == '&' && input[i + 1] == '&')
    {
        op[0] = '&'; op[1] = '&'; op[2] = '\0';
        return (2);
    }
    if (input[i] == '<' && input[i + 1] == '<')
    {
        op[0] = '<'; op[1] = '<'; op[2] = '\0';
        return (2);
    }
    if (input[i] == '>' && input[i + 1] == '>')
    {
        op[0] = '>'; op[1] = '>'; op[2] = '\0';
        return (2);
    }
    op[0] = input[i];
    op[1] = '\0';
    return (1);
}

static void handle_special_char(t_utils_lexer *storage,
                                const char *input,
                                t_token **tokens)
{
    char   op[3];
    size_t len;

    /* 1) terminer le mot en cours */
    flush_buffer(storage, tokens, false);

    /* 2) récupérer l’opérateur et sa longueur */
    len = get_operator(input, storage->i, op);

    /* 3) créer le token */
    add_token_or_segment(tokens, op, QUOTE_NONE, false);

    /* 4) avancer l’index de 1 ou 2 */
    storage->i += (len - 1);

    /* 5) on vient de sortir d’un opérateur */
    storage->new_arg = false;
}

void	process_normal_char(t_utils_lexer *storage,
							const char *input,
							t_token **tokens)
{
	if (ft_iswhitespace(storage->c))
		handle_space(storage, tokens);
	else if (storage->c == '\'')
	{
		enter_quote_state(storage,
			tokens,
			LEXER_SINGLE_QUOTE,
			QUOTE_SINGLE);
	}
	else if (storage->c == '\"')
	{
		enter_quote_state(storage,
			tokens,
			LEXER_DOUBLE_QUOTE,
			QUOTE_DOUBLE);
	}
	else if (is_special_char(storage->c))
	{
		handle_special_char(storage, input, tokens);
	}
	else
		handle_default_char(storage);
}
