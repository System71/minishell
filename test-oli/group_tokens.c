/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/14 20:08:57 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

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

// Fusion des segments de deux tokens T_WORD.
// On attache une copie des segments du token 'next' à la fin de 'curr'.
static void merge_word_tokens(t_token *curr, t_token *next)
{ 
	// Trouver le dernier segment de curr.
	t_token_segment *last_seg = curr->segments;
	while (last_seg && last_seg->next)
		last_seg = last_seg->next;
	// Attacher une copie des segments du token suivant.
	if (last_seg)
		last_seg->next = duplicate_segments(next->segments);
	else
		curr->segments = duplicate_segments(next->segments);
}

// La fonction principale de regroupement.
t_token *group_tokens(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		// 1. Fusionner les tokens T_WORD consécutifs 
		if (curr->type == T_WORD)
		{
			while (curr->next && curr->next->type == T_WORD)
			{
				merge_word_tokens(curr, curr->next);
				// On retire le token suivant de la liste.
 				t_token *to_remove = curr->next;
				curr->next = to_remove->next;
				free(to_remove);
			}
		}
		// 2. Regroupement pour les redirections
		else if (is_redirection(curr->type))
		{
			if (curr->next && curr->next->type == T_WORD)
			{
				// On supprime les segments du token de redirection (le signe) et on y attache la cible.
 				free_token_segments(curr);
				curr->segments = duplicate_segments(curr->next->segments);
				// On retire le token cible de la liste.
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

