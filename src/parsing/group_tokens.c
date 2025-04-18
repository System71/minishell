/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/16 09:03:58 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"
#include <stdio.h>
// Renvoie vrai si le type correspond à une redirection. 
static int is_redirection(t_token_type type)
{ 
	return (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_APPEND || type == T_HEREDOC);
}

// Duplication récursive d'une liste de segments.
static t_token_segment *duplicate_segments(t_token_segment *seg)
{
	if (!seg)
		return NULL;
	t_token_segment *new_seg = create_segment(seg->content, seg->quote);
	if (!new_seg) return NULL;
	// Gérer l'erreur selon vos préférences
	new_seg->next = duplicate_segments(seg->next);
	return new_seg;
}

// Libère la liste de segments d'un token.
static void free_token_segments(t_token *token)
{
	t_token_segment *seg = token->segments;
	while (seg)
	{
		t_token_segment *tmp = seg;
		seg = seg->next;
		free(tmp->content);
		free(tmp);
	} 
	token->segments = NULL;
}

t_token *group_tokens(t_token *tokens)
{
    t_token *curr = tokens;
    while (curr)
    {
        // Ne rien faire si le token est de type T_WORD.
        // On se contente uniquement de traiter les redirections.
        if (is_redirection(curr->type))
        {
            if (curr->next && curr->next->type == T_WORD)
            {
                // Pour un opérateur de redirection, on veut que le token suivant (cible)
                // soit "attaché" au token redirection, en remplaçant ses segments actuels (souvent le signe)
                // par ceux du token cible.
                free_token_segments(curr);
                curr->segments = duplicate_segments(curr->next->segments);
                // On retire le token cible de la chaîne.
                t_token *to_remove = curr->next;
                curr->next = to_remove->next;
                free(to_remove);
            }
            else
            {
                fprintf(stderr, "Erreur syntaxique: opérateur de redirection sans cible.\n");
            }
        }
        curr = curr->next;
    }
    return tokens;
}
