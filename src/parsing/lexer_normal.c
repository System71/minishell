/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 10:32:19 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/lib_utils.h"
#include "../memory/mem.h"
#include <stdio.h>

static void	handle_space(t_utils_lexer *storage, t_token **tokens)
{
	flush_buffer(storage, tokens, false);
	storage->new_arg = true;
}

/*static void	handle_special_char(t_utils_lexer *storage,*/
/*								const char *input,*/
/*								t_token **tokens)*/
/*{*/
/*	char	dbl[3];*/
/*	char	single[2];*/
/**/
/*	flush_buffer(storage, tokens, false);*/
/*	if ((storage->c == '>' || storage->c == '<')*/
/*		&& input[storage->i + 1] != '\0'*/
/*		&& input[storage->i + 1] == storage->c)*/
/*	{*/
/*		dbl[0] = storage->c;*/
/*		dbl[1] = storage->c;*/
/*		dbl[2] = '\0';*/
/*		add_token_or_segment(tokens, dbl, QUOTE_NONE, false);*/
/*		storage->i++;*/
/*	}*/
/*	else*/
/*	{*/
/*		single[0] = storage->c;*/
/*		single[1] = '\0';*/
/*		add_token_or_segment(tokens, single, QUOTE_NONE, false);*/
/*	}*/
/*	storage->new_arg = false;*/
/*}*/
/**/

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
static void handle_special_char(t_utils_lexer *storage,
                                const char *input,
                                t_token **tokens)
{
    char op[3];
    size_t len = 1;              // longueur de l’op inhérente (1 ou 2)
    
    // 1) on termine le mot en cours
    flush_buffer(storage, tokens, false);

    // 2) on détecte en priorité les doubles opérateurs
    if (storage->c == '|' && input[storage->i + 1] == '|')
    {
        op[0] = '|'; op[1] = '|'; op[2] = '\0';
        len = 2;
    }
    else if (storage->c == '&' && input[storage->i + 1] == '&')
    {
        op[0] = '&'; op[1] = '&'; op[2] = '\0';
        len = 2;
    }
    else if (storage->c == '<' && input[storage->i + 1] == '<')
    {
        op[0] = '<'; op[1] = '<'; op[2] = '\0';
        len = 2;
    }
    else if (storage->c == '>' && input[storage->i + 1] == '>')
    {
        op[0] = '>'; op[1] = '>'; op[2] = '\0';
        len = 2;
    }
    // 3) ou bien un opérateur simple
    else
    {
        op[0] = storage->c;
        op[1] = '\0';
        len = 1;
    }

    // 4) on crée un token (toujours mergeable = false pour un opérateur)
    add_token_or_segment(tokens, op, QUOTE_NONE, false);

    // 5) on déplace l’index de 1 ou 2
    storage->i += (len - 1);

    // 6) on marque qu’on vient de sortir d’un opérateur
    storage->new_arg = false;
}

void	process_normal_char(t_utils_lexer *storage,
							const char *input,
							t_token **tokens)
{
	if (isspace(storage->c))
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
/*void process_normal_char(t_utils_lexer *s,*/
/*                         const char *input,*/
/*                         t_token **tokens)*/
/*{*/
/*    char c = s->c;*/
/**/
/*    if (isspace(c))*/
/*        handle_space(s, tokens);*/
/*    else if (c == '\'')*/
/*        enter_quote_state(s, tokens,*/
/*                          LEXER_SINGLE_QUOTE, QUOTE_SINGLE);*/
/*    else if (c == '\"')*/
/*        enter_quote_state(s, tokens,*/
/*                          LEXER_DOUBLE_QUOTE, QUOTE_DOUBLE);*/
/*    else if (is_special_char(c))*/
/*        handle_special_char(s, input, tokens);*/
/*    else*/
/*        handle_default_char(s);*/
/*}*/
