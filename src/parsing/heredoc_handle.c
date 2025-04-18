/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:56:33 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/17 07:47:21 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

// Fonction d'aide pour concaténer une ligne lue (avec ajout d'un '\n') à un buffer existant.
static char *append_line(char *dest, const char *line)
{
	size_t old_len = dest ? strlen(dest) : 0;
	size_t line_len = strlen(line);
	// On ajoute 1 pour le '\n' et 1 pour le '\0'
	size_t new_len = old_len + line_len + 2;
	char *new_str = realloc(dest, new_len);
	if (!new_str)
	{
		free(dest);
		return NULL;
	}
	// Copier la nouvelle ligne à la suite
	memcpy(new_str + old_len, line, line_len);
	new_str[old_len + line_len] = '\n';
	// Ajout du saut de ligne
	new_str[old_len + line_len + 1] = '\0';
	return new_str;
}

// Fonction de gestion du heredoc.
// Parcourt la liste des tokens et, pour chaque token de type T_HEREDOC,
// lit les lignes jusqu'au délimiteur et remplace le contenu du token par le contenu du heredoc.
int heredoc_handle(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		if (curr->type == T_HEREDOC)
		{
			// On suppose que le premier segment du token contient le délimiteur.
			char *delimiter = curr->segments->content;
			/*int quote = curr->segments->quote;*/
			// On garde cette information pour l'expansion.
			char *heredoc_content = NULL;
			char *line = NULL;
			// Affichage du prompt heredoc. On peut choisir le prompt voulu (ici "> ")
			while ((line = readline("> ")) != NULL)//ET SIGNAUX
			{
				// Comparaison stricte : si la ligne saisie correspond exactement au délimiteur, on arrête.
				if (strcmp(line, delimiter) == 0)
				{
					free(line);
					break;
				}
				heredoc_content = append_line(heredoc_content, line);
				free(line);
			}
			// Remplacer le contenu du premier segment par le contenu du heredoc
			free(curr->segments->content);
			// Si heredoc_content est NULL, on le remplace par une chaîne vide pour éviter un problème.
			curr->segments->content = heredoc_content ? heredoc_content : strdup("");
			// Le champ 'quote' reste inchangé afin qu'à l'étape d'expansion on puisse savoir
			// si le contenu doit être expansé (exemple : avec ou sans expansion des variables).
		}
		curr = curr->next;
	}
	return 0;
}
