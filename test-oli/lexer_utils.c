/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/14 20:13:15 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
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

/* --- Structures de segments --- */
/* Crée un segment de token */
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

/* Ajoute un segment à un token (en fin de liste des segments) */
static void add_segment_to_token(t_token *token, const char *content, t_quote_type quote)
{
    t_token_segment *new_seg = create_segment(content, quote);
    if (!new_seg)
        return; // Gérer l'erreur comme tu veux
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

/* Crée un nouveau token de type T_WORD initialisé avec un segment */
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

/* Ajoute un token à la liste globale.
   Si mergeable est vrai et le dernier token existe et est de type T_WORD,
   on ajoute le segment au dernier token, sinon on crée un nouveau token. */
static void add_token_or_segment(t_token **tokens, const char *content, t_quote_type quote, bool mergeable)
{
    if (!*tokens || !mergeable)
    {
        t_token *new_token = create_token_with_segment(content, quote);
        if (!new_token)
            return; // Gérer l'erreur
        if (!*tokens)
            *tokens = new_token;
        else
        {
            t_token *tmp = *tokens;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new_token;
        }
    }
    else
    {
        /* mergeable == true : on ajoute un segment au dernier token si celui-ci est de type T_WORD */
        t_token *tmp = *tokens;
        while (tmp->next)
            tmp = tmp->next;
        if (tmp->type == T_WORD)
            add_segment_to_token(tmp, content, quote);
        else
        {
            /* Si le dernier token n'est pas T_WORD, créer un nouveau token */
            t_token *new_token = create_token_with_segment(content, quote);
            tmp->next = new_token;
        }
    }
}


/* --- Fonction flush_buffer --- */
/* Vide le buffer dynamique et crée un segment dans un token T_WORD.
   Le booléen mergeable indique si le segment doit être fusionné avec le dernier token existant. */
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
void process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens)
{
	if (isspace(storage->c))
	{
		/* Espace : fin de segment, on ne fusionne pas avec le suivant */
		flush_buffer(storage, tokens, false);
		storage->new_arg = true;
	}
	else if (storage->c == '\'')
	{
		if (storage->new_arg == true)
			flush_buffer(storage, tokens, false);
		else
			flush_buffer(storage, tokens, true);
		storage->state = LEXER_SINGLE_QUOTE;
		storage->current_quote = QUOTE_SINGLE;
	}
	else if (storage->c == '\"')
	{
		if (storage->new_arg == true)
			flush_buffer(storage, tokens, false);
		else
			flush_buffer(storage, tokens, true);

		storage->state = LEXER_DOUBLE_QUOTE;
		storage->current_quote = QUOTE_DOUBLE;
	}
	else if (is_special_char(storage->c))
	{
		flush_buffer(storage, tokens, false);
		/* Gère le cas des opérateurs doublés (>> ou <<) */
		if ((storage->c == '>' || storage->c == '<') &&
			input[storage->i + 1] != '\0' && input[storage->i + 1] == storage->c)
		{
			char dbl[3] = { storage->c, storage->c, '\0' };
			/* Pour les opérateurs spéciaux, on crée toujours un nouveau token */
			add_token_or_segment(tokens, dbl, QUOTE_NONE, false);
			storage->i++;  /* On saute le deuxième caractère */
		}
		else
	{
			char single[2] = { storage->c, '\0' };
			add_token_or_segment(tokens, single, QUOTE_NONE, false);
		}
		storage->new_arg = false;
	}
	else
	{
		/*// Avant d'ajouter, si le flag new_arg est true et que le buffer est vide,*/
		/*// cela signifie qu'on doit démarrer un nouvel argument*/
		/*if (storage->new_arg && storage->buffer->len == 0)*/
		/*{*/
		/*	// On force la création d'un nouveau token en appelant flush_buffer avec mergeable = false.*/
		/*	// (Si le buffer est vide, flush_buffer ne fera rien, alors on pourra forcer la création*/
		/*	// d'un token vide que l'on pourra compléter avec les caractères suivants.)*/
		/*	// On flush pas ici on add_token c est normal ?*/
		/*	add_token_or_segment(tokens, "", QUOTE_NONE, false);*/
		/*	storage->new_arg = false;*/
		/*}*/

		/* Caractère normal : on l'ajoute au buffer dynamique */
		if (!append_char(storage->buffer, storage->c))
		{
			fprintf(stderr, "Error: Allocation failed in append_char\n");
			exit(EXIT_FAILURE);
		}
	}
}

void process_quote_char(t_utils_lexer *storage, t_token **tokens)
{
    /* Si le caractère courant correspond à la quote fermante,
       on termine le mode quote */
    if ((storage->state == LEXER_SINGLE_QUOTE && storage->c == '\'') ||
        (storage->state == LEXER_DOUBLE_QUOTE && storage->c == '\"'))
    {
		if (storage->new_arg == true)
			flush_buffer(storage, tokens, false);
		else
			flush_buffer(storage, tokens, true);
        storage->state = LEXER_NORMAL;
		storage->new_arg = false;
    }
    else
    {
        if (!append_char(storage->buffer, storage->c))
        {
            fprintf(stderr, "Error: Allocation failed in append_char\n");
            exit(EXIT_FAILURE);
        }
    }
}
