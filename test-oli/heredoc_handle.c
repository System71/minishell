/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:56:33 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/11 08:50:31 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char *read_here_doc(const char *delimiter);

int heredoc_handle(t_token *tokens)
{
    char *here_doc_content;
    t_token *delim;

    // Parcours la liste des tokens
    while (tokens)
    {
        // Si on rencontre un token here_doc (qui contient l'opérateur <<)
        if (tokens->type == T_HEREDOC)
        {
            // Le token suivant doit être le délimiteur
            delim = tokens->next;
            if (delim && delim->type == T_WORD)
            {
                // Conserver l'information du type de quote du délimiteur
                tokens->quote = delim->quote;

                // Lire le contenu du here_doc jusqu'au délimiteur
                here_doc_content = read_here_doc(delim->content);
                if (!here_doc_content)
                {
                    fprintf(stderr, "Error: here_doc reading failed\n");
                    return (-1);
                }

                // Supprimer le token délimiteur de la chaîne
                // Pour cela, on lie le here_doc token au token qui suit le délimiteur
                tokens->next = delim->next;
                
                // Libérer le token délimiteur (et son contenu)
                free(delim->content);
                free(delim);

                // Remplacer le contenu du token here_doc par le contenu recueilli
                if (tokens->content)
                    free(tokens->content);
                tokens->content = strdup(here_doc_content);
                if (!tokens->content)
                {
                    printf("Error: allocation failed for here_doc content\n");
                    free(here_doc_content);
                    return (-1);
                }
                free(here_doc_content);
            }
            else
            {
                // Si aucun délimiteur n'est trouvé, signaler une erreur
                printf("Error: here_doc without delimiter.\n");
                return (-1);
            }
        }
        // Passer au token suivant dans la chaîne
        tokens = tokens->next;
    }
    return (0);
}
char *ft_strjoin(const char *s1, const char *s2) {
	size_t len1 = strlen(s1), len2 = strlen(s2);
	char *res = malloc(len1 + len2 + 1);
	if (!res) return NULL;
	memcpy(res, s1, len1);
	memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return res;
}

char *read_here_doc(const char *delimiter)
{
	char *line;
	char *here_content = strdup(""); // contenu initial vide
	char *tmp;

	if (!here_content)
		return NULL;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		// On concatène la ligne et un retour à la ligne
		tmp = here_content;
		here_content = ft_strjoin(here_content, line);
		free(tmp);
		tmp = here_content;
		here_content = ft_strjoin(here_content, "\n");
		free(tmp);
		free(line);
	}
	return here_content;
}
