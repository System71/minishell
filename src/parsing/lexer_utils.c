/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/23 15:12:30 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

t_token_type get_token_type(const char *str)
{
    if (strcmp(str, "|") == 0)
        return T_PIPE;
    else if (strcmp(str, "<") == 0)
        return T_REDIRECT_IN;
    else if (strcmp(str, ">") == 0)
        return T_REDIRECT_OUT;
    else if (strcmp(str, ">>") == 0)
        return T_APPEND;
    else if (strcmp(str, "<<") == 0)
        return T_HEREDOC;
    return T_WORD;
}

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

t_token_segment *create_segment(const char *content, t_quote_type quote)
{
    t_token_segment *seg = malloc(sizeof(t_token_segment));
    if (!seg)
        return NULL;
    seg->content = strdup(content);
    if (!seg->content) {
        free(seg);
        return NULL;
    }
    seg->quote = quote;
    seg->next = NULL;
    return seg;
}

static void add_segment_to_token(t_token *token, const char *content, t_quote_type quote)
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

static t_token *create_token_with_segment(const char *content, t_quote_type quote)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->type = get_token_type(content);
    token->segments = create_segment(content, quote);
    token->next = NULL;
    return token;
}
// 1) Récupère le dernier token de la liste (ou NULL si la liste est vide)
static t_token *get_last_token(t_token *tokens)
{
    if (!tokens)
        return NULL;
    while (tokens->next)
        tokens = tokens->next;
    return tokens;
}

// 2) Crée un token avec un segment et l'ajoute à la fin de *tokens
static void append_new_token(t_token **tokens,
                             const char *content,
                             t_quote_type quote)
{
    t_token *new_token = create_token_with_segment(content, quote);
    if (!new_token)
        return; // TODO: gérer l’erreur si besoin

    if (!*tokens)
        *tokens = new_token;
    else
        get_last_token(*tokens)->next = new_token;
}

// 3) Si le dernier token est un mot, on y ajoute un segment,
//    sinon on tombe dans le cas « append_new_token »
static void add_or_append_segment(t_token **tokens,
                                  const char *content,
                                  t_quote_type quote)
{
    t_token *last = get_last_token(*tokens);
    if (last && last->type == T_WORD)
    {
        add_segment_to_token(last, content, quote);
    }
    else
    {
        append_new_token(tokens, content, quote);
    }
}

// 4) La fonction d’origine, refaite en 5 lignes claires
static void add_token_or_segment(t_token **tokens,
                                 const char *content,
                                 t_quote_type quote,
                                 bool mergeable)
{
    if (!*tokens || !mergeable)
        append_new_token(tokens, content, quote);
    else
        add_or_append_segment(tokens, content, quote);
}

/*static void add_token_or_segment(t_token **tokens, const char *content, t_quote_type quote, bool mergeable)*/
/*{*/
/*    if (!*tokens || !mergeable)*/
/*    {*/
/*        t_token *new_token = create_token_with_segment(content, quote);*/
/*        if (!new_token)*/
/*            return; // Gérer l'erreur*/
/*        if (!*tokens)*/
/*            *tokens = new_token;*/
/*        else*/
/*        {*/
/*            t_token *tmp = *tokens;*/
/*            while (tmp->next)*/
/*                tmp = tmp->next;*/
/*            tmp->next = new_token;*/
/*        }*/
/*    }*/
/*    else*/
/*    {*/
/*        t_token *tmp = *tokens;*/
/*        while (tmp->next)*/
/*            tmp = tmp->next;*/
/*        if (tmp->type == T_WORD)*/
/*            add_segment_to_token(tmp, content, quote);*/
/*        else*/
/*        {*/
/*            t_token *new_token = create_token_with_segment(content, quote);*/
/*            tmp->next = new_token;*/
/*        }*/
/*    }*/
/*}*/


void flush_buffer(t_utils_lexer *storage, t_token **tokens, bool mergeable)
{
    if (storage->buffer->len > 0)
    {
        storage->buffer->data[storage->buffer->len] = '\0';
        add_token_or_segment(tokens, storage->buffer->data, storage->current_quote, mergeable);
        storage->buffer->len = 0;
        storage->buffer->data[0] = '\0';
        storage->current_quote = QUOTE_NONE;
    }
}

static void handle_space(t_utils_lexer *storage, t_token **tokens)
{
    flush_buffer(storage, tokens, false);
    storage->new_arg = true;
}

static void enter_quote_state(t_utils_lexer *storage,
                              t_token **tokens,
                              t_lexer_state     new_state,
                              t_quote_type new_quote)
{
    if (storage->new_arg == true)
    {
        if (storage->buffer->len > 0)
        {
            storage->new_arg = false;
        }
        flush_buffer(storage, tokens, false);
    }
    else
    {
        flush_buffer(storage, tokens, true);
    }
    storage->state         = new_state;
    storage->current_quote = new_quote;
}

static void handle_special_char(t_utils_lexer *storage,
                                const char     *input,
                                t_token        **tokens)
{
    char      dbl[3];
    char      single[2];

    flush_buffer(storage, tokens, false);
    if ((storage->c == '>' || storage->c == '<')
        && input[storage->i + 1] != '\0'
        && input[storage->i + 1] == storage->c)
    {
        dbl[0] = storage->c;
        dbl[1] = storage->c;
        dbl[2] = '\0';
        add_token_or_segment(tokens, dbl, QUOTE_NONE, false);
        storage->i++;
    }
    else
    {
        single[0] = storage->c;
        single[1] = '\0';
        add_token_or_segment(tokens, single, QUOTE_NONE, false);
    }
    storage->new_arg = false;
}

static void handle_default_char(t_utils_lexer *storage)
{
    bool ok;

    ok = append_char(storage->buffer, storage->c);
    if (!ok)
    {
        printf("Error: Allocation failed in append_char\n");
        exit(EXIT_FAILURE);
    }
}

void process_normal_char(t_utils_lexer *storage,
                         const char     *input,
                         t_token        **tokens)
{
    if (isspace(storage->c))
    {
        handle_space(storage, tokens);
    }
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
    {
        handle_default_char(storage);
    }
}

/*void process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens)*/
/*{*/
/*	if (isspace(storage->c))*/
/*	{*/
/*		flush_buffer(storage, tokens, false);*/
/*		storage->new_arg = true;*/
/*	}*/
/*	else if (storage->c == '\'')*/
/*	{*/
/*		if (storage->new_arg == true)*/
/*		{	*/
/*			if (storage->buffer->len > 0)*/
/*				storage->new_arg = false;*/
/*			flush_buffer(storage, tokens, false);*/
/*		}*/
/*		else*/
/*			flush_buffer(storage, tokens, true);*/
/*		storage->state = LEXER_SINGLE_QUOTE;*/
/*		storage->current_quote = QUOTE_SINGLE;*/
/*	}*/
/*	else if (storage->c == '\"')*/
/*	{*/
/*		if (storage->new_arg == true)*/
/*		{*/
/*			if (storage->buffer->len > 0)*/
/*				storage->new_arg = false;*/
/*			flush_buffer(storage, tokens, false);*/
/*		}*/
/*		else*/
/*			flush_buffer(storage, tokens, true);*/
/**/
/*		storage->state = LEXER_DOUBLE_QUOTE;*/
/*		storage->current_quote = QUOTE_DOUBLE;*/
/*	}*/
/*	else if (is_special_char(storage->c))*/
/*	{*/
/*		flush_buffer(storage, tokens, false);*/
/*		if ((storage->c == '>' || storage->c == '<') &&*/
/*			input[storage->i + 1] != '\0' && input[storage->i + 1] == storage->c)*/
/*		{*/
/*			char dbl[3] = { storage->c, storage->c, '\0' };*/
/*			add_token_or_segment(tokens, dbl, QUOTE_NONE, false);*/
/*			storage->i++;*/
/*		}*/
/*		else*/
/*	{*/
/*			char single[2] = { storage->c, '\0' };*/
/*			add_token_or_segment(tokens, single, QUOTE_NONE, false);*/
/*		}*/
/*		storage->new_arg = false;*/
/*	}*/
/*	else*/
/*	{*/
/*		if (!append_char(storage->buffer, storage->c))*/
/*		{*/
/*			printf("Error: Allocation failed in append_char\n");*/
/*			exit(EXIT_FAILURE);*/
/*		}*/
/**/
/*	}*/
/*}*/

void process_quote_char(t_utils_lexer *storage, t_token **tokens)
{
    if ((storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'') ||
        (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"'))
    {
		if (storage->new_arg == true)
		{
			storage->new_arg = false;
			flush_buffer(storage, tokens, false);
		}
		else
			flush_buffer(storage, tokens, true);
        storage->state = LEXER_NORMAL;
    }
    else
    {
        if (!append_char(storage->buffer, storage->c))
        {
            printf("Error: Allocation failed in append_char\n");
            exit(EXIT_FAILURE);
        }
    }
}
