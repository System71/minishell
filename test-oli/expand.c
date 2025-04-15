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
#include "types.h"

// On suppose que last_exit_code est une variable mise à jour après chaque commande.
int last_exit_code = 0;

// Fonction d'aide pour concaténer dynamiquement une chaîne.
static void append_str(char **dest, const char *src)
{
	size_t old_len = *dest ? strlen(*dest) : 0;
	size_t src_len = strlen(src);
	char *new_str = realloc(*dest, old_len + src_len + 1);
	if (!new_str)
	{
		free(*dest);
		exit(EXIT_FAILURE);
	}
	memcpy(new_str + old_len, src, src_len);
	new_str[old_len + src_len] = '\0';
	*dest = new_str;
}

// Fonction qui effectue l'expansion d'une chaîne selon le type de quote.
// Si quote == QUOTE_SINGLE, on ne fait aucune expansion.
char *check_expand(const char *input, t_quote_type quote)
{
	// Si on est dans des quotes simples, renvoyer une copie de la chaîne.
	if (quote == QUOTE_SINGLE)
		return strdup(input);
	char *result = NULL;
	size_t i = 0;
	while (input[i]) {
		// Si on détecte un '$'
		if (input[i] == '$') {
			// Cas spécial $? : on remplace par le code de sortie de la dernière commande.
			if (input[i + 1] == '?') {
				char buffer[32];
				snprintf(buffer, sizeof(buffer), "%d", last_exit_code);
				append_str(&result, buffer);
				i += 2; // on saute $ et ?
				continue;
			}
			// Cas d'une variable d'environnement (nom composé de lettres, chiffres ou _).
			else if ( (isalpha(input[i + 1]) || input[i + 1] == '_') )
			{
				size_t var_start = i + 1;
				size_t var_len = 0;
				while (input[var_start + var_len] &&
					(isalnum(input[var_start + var_len]) || input[var_start + var_len] == '_'))
				{
					var_len++;
				}
				char *var_name = strndup(input + var_start, var_len);
				char *var_value = getenv(var_name);
				free(var_name);
				// Si la variable n'existe pas, on insère une chaîne vide.
				if (var_value)
					append_str(&result, var_value);
				else
					append_str(&result, "");
				i += 1 + var_len;
				continue;
			}
			// Sinon, ce n'est pas une expansion valide, on ajoute simplement le '$'
			else {
				append_str(&result, "$");
				i++;
				continue;
			}
		}
		else {
			// On ajoute le caractère courant au résultat.
			char tmp[2] = { input[i], '\0' };
			append_str(&result, tmp);
			i++;
		}
	}
	// Retourne la chaîne construite.
	return result;

}


void expand_handle(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		t_token_segment *seg = curr->segments;
		while (seg)
		{
			// Remplacer le contenu du segment par le contenu expansé.
	 		char *expanded = check_expand(seg->content, seg->quote);
			free(seg->content);
			seg->content = expanded;
			seg = seg->next;
		}
		curr = curr->next;
	}
}

