/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/11 09:54:59 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

char *check_expand(const char *input, t_quote_type quote)
{
	size_t i;
	size_t k;
	
	i = 0;
	k = 0;
	// Si le token est entre quotes simples, on ne fait aucune expansion.
    if (quote == QUOTE_SINGLE)
        return strdup(input);

    t_dynamic_buffer *result = init_dynamic_buffer();
    if (!result)
        return NULL;

    // Parcours de l'entrée caractère par caractère
    while (input[i] != '\0')
    {
        // Si on rencontre le signe '$', tenter d'identifier une variable
        if (input[i] == '$')
        {
            size_t j = i + 1;

            // Ici, tu peux ajouter des cas spéciaux ($$, $?, etc.) si nécessaire.
            // Pour l'instant, on suppose que seule une variable d'environnement est concernée.
            while (isalnum(input[j]) || input[j] == '_')
                j++;
            
            // S'il n'y a pas de variable (ex. "$ " ou "$,") on traite '$' comme caractère normal.
            if (j == i + 1)
            {
                append_char(result, input[i]);
                continue;
            }

            // Extraction du nom de la variable
            size_t var_len = j - (i + 1);
            char *var_name = strndup(input + i + 1, var_len);
            if (!var_name)
            {
                free_dynamic_buffer(result);
                return NULL;
            }

            // Recherche de la valeur dans l'environnement
            char *var_value = getenv(var_name);
            free(var_name);

            // Si la variable existe, on copie sa valeur dans le buffer
            if (var_value)
            {
                while (var_value[k] != '\0')
                {
                    if (!append_char(result, var_value[k]))
                    {
                        free_dynamic_buffer(result);
                        return NULL;
                    }
					k++;
                }
            }
            // Sinon, on remplace par une chaîne vide (i.e. rien)

            // Mettre à jour l'indice pour sauter le nom de la variable déjà traité
            i = j - 1; 
        }
        else
        {
            // Caractère normal : on l'ajoute au buffer
            if (!append_char(result, input[i]))
            {
                free_dynamic_buffer(result);
                return NULL;
            }
        }
		i++;
    }
    // On duplique le contenu final du buffer
    char *expanded = strdup(result->data);
    free_dynamic_buffer(result);
    return expanded;
}


void expand_handle(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type == T_WORD &&
            (tokens->quote == QUOTE_DOUBLE || tokens->quote == QUOTE_NONE))
        {
            char *expanded = check_expand(tokens->content, tokens->quote);
            if (expanded)
            {
                free(tokens->content);
                tokens->content = expanded;
            }
        }
        tokens = tokens->next;
    }
}

