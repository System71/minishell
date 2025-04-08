/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/08 13:56:58 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

t_token *group_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current && current->next)
    {
        // Fusionner uniquement si le token suivant est marquée comme fusionnable.
        if (current->mergeable)
        {
            size_t len1 = strlen(current->content);
            size_t len2 = strlen(current->next->content);
            char *new_content = malloc(len1 + len2 + 1);
            if (!new_content)
            {
                fprintf(stderr, "Error: allocation failed in group_tokens\n");
                exit(EXIT_FAILURE);
            }
            strcpy(new_content, current->content);
            strcat(new_content, current->next->content);
            free(current->content);
            current->content = new_content;
            // Le token fusionné hérite d'un mergeable de current (ou vous le mettez à false).
            current->mergeable = current->next->mergeable;
            // On retire le token fusionné
            t_token *temp = current->next;
            current->next = temp->next;
            free(temp->content);
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
    return tokens;
}
