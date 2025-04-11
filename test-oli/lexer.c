/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:46:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/11 12:18:55 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

void	init_utils_lexer(t_utils_lexer *storage)
{
	storage->state = LEXER_NORMAL;
    storage->buffer = init_dynamic_buffer();
	storage->i = 0;
    storage->current_quote = QUOTE_NONE;

}

/*t_token *lexer(const char *input)*/
/*{*/
/*    t_token			*tokens;*/
/*	t_utils_lexer	storage;*/
/**/
/*	tokens = NULL;*/
/*	init_utils_lexer(&storage);*/
/*    while (input[storage.i] != '\0')*/
/*    {*/
/*        storage.c = input[storage.i];*/
/**/
/*        if (storage.state == LEXER_NORMAL)*/
/*        {*/
/*			process_normal_char(&storage, input, &tokens);*/
/*        }*/
/*        else*/
/*		{*/
/*			process_quote_char(&storage);*/
/*        }*/
/*		storage.i++;*/
/*    }*/
/*    flush_buffer(&storage, &tokens, false);//WARNING FALSE maybe TRUE*/
/*	if (storage.state != LEXER_NORMAL)*/
/*	{*/
/*		printf("Error quote ! \n");*/
/*       // Ici, tu pourrais renvoyer NULL ou gérer l'erreur selon ta logique.*/
/*	}*/
/*    return tokens;*/
/*}*/

t_token *lexer(const char *input)
{
    t_token *tokens = NULL;
    t_utils_lexer storage;

    /* Initialisation du contexte */
    storage.state = LEXER_NORMAL;
    storage.i = 0;
    storage.c = '\0';
    storage.buffer = init_dynamic_buffer();
    storage.current_quote = QUOTE_NONE;

    while (input[storage.i] != '\0')
    {
        storage.c = input[storage.i];
        
        if (storage.state == LEXER_NORMAL)
        {
            process_normal_char(&storage, input, &tokens);
        }
        else
        {
            process_quote_char(&storage);
        }
        storage.i++;
    }
    /* Vider le buffer pour le dernier segment */
    flush_buffer(&storage, &tokens, false);

    if (storage.state != LEXER_NORMAL)
    {
        printf("Error: unclosed quote!\n");
    }
    free_dynamic_buffer(storage.buffer);
    return tokens;
}
