/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/08 11:54:08 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

char *expand_variables(const char *input, t_quote_type quote)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
    // Si le token est entre quotes simples, on retourne simplement une copie
    if (quote == QUOTE_SINGLE)
        return strdup(input);

    // Pour QUOTE_DOUBLE ou QUOTE_NONE, on parcourt la chaîne à la recherche du caractère '$'
    // et on remplace chaque occurrence par la valeur de la variable d'environnement correspondante.
    // Une approche simple consiste à allouer un buffer dynamique (comme dans le lexer)
    // et à y copier le résultat avec les substitutions.
    //
    // Cette fonction est à adapter selon la complexité que tu souhaites supporter.
    // Voici une version très simplifiée :

    t_dynamic_buffer *result = init_dynamic_buffer();
    if (!result)
        return NULL;

    while (input[i] != '\0')
	{
        if (input[i] == '$')
		{
            // On identifie la variable : on suppose ici qu'elle est constituée de lettres, chiffres et '_'
            size_t j = i + 1;
            while (isalnum(input[j]) || input[j] == '_')
                j++;
            size_t var_len = j - (i + 1);
            char *var_name = strndup(&input[i + 1], var_len);
            char *var_value = getenv(var_name);
            free(var_name);
            // Si la variable n'existe pas, on peut la remplacer par une chaîne vide.
            if (var_value)
			{
                while (var_value[k] != '\0')
				{
                    append_char(result, var_value[k]);
					k++;
                }
            }
            // On saute le nom de variable
            i = j - 1;
        } else
		{
            append_char(result, input[i]);
        }
	i++;
    }
    char *expanded = strdup(result->data);
    free_dynamic_buffer(result);
    return expanded;
}

