/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/03 20:11:58 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	manage_redirect_in(t_token **tokens, t_command **current_cmd);
void	manage_pipe(t_token **tokens, t_command **current_cmd);
void	manage_redirect_out(t_token **tokens, t_command **current_cmd);
char *read_here_doc(const char *delimiter);

t_command *parser(t_token *tokens)
{
	t_command *head = NULL;
	t_command *current_cmd = NULL;

	while (tokens)
	{
		if (!head)
		{
			head = create_command();
			current_cmd = head;
		}
		if (tokens->type == T_HEREDOC)
		{
			// Le token suivant est supposé contenir le délimiteur.
			if (tokens->next && tokens->next->type == T_WORD)
			{
				char *delimiter = tokens->next->content;
				char *here_doc_content = read_here_doc(delimiter);
				// Par exemple, tu peux stocker ici_doc_content dans current_cmd
				// ou créer un token spécifique pour le contenu du here_doc.
				add_argument(current_cmd, tokens, T_HEREDOC); // ou un nouveau type, par exemple T_HEREDOC_CONTENT
				// Ici, tu pourrais par exemple remplacer le contenu du token T_HEREDOC :
				free(tokens->content);
				tokens->content = here_doc_content;

				// Passe le token du délimiteur pour ne pas le traiter à nouveau
				tokens = tokens->next;
			}
			else
		{
				printf("Erreur : here_doc sans délimiteur.\n");
			}
		}
		if (tokens->type == T_WORD ||
			tokens->type == T_SINGLE_QUOTE ||
			tokens->type == T_DOUBLE_QUOTE )
		{
			/*printf("HERE\n");*/

			add_argument(current_cmd, tokens, tokens->type);
		}
		if (tokens->type == T_PIPE)
		{
			manage_pipe(&tokens, &current_cmd);
		}
		if (tokens->type == T_REDIRECT_IN)
		{
			manage_redirect_in(&tokens, &current_cmd);
		}
		if (tokens->type == T_REDIRECT_OUT )
		{
			manage_redirect_out(&tokens, &current_cmd);
		}
		tokens = tokens->next;
	}
	return head;
}
void	manage_pipe(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not cmd after <\n");
		return;
	}
	*tokens = (*tokens)->next;	
	add_argument(*current_cmd, *tokens, T_PIPE);
	(*current_cmd)->next = create_command();
    *current_cmd = (*current_cmd)->next;
}
void	manage_redirect_in(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not name of file after <\n");
		return;
	}
	*tokens = (*tokens)->next;
	add_argument(*current_cmd, *tokens, T_REDIRECT_IN);

}
void	manage_redirect_out(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not name of file after <\n");
		return;
	}
	*tokens = (*tokens)->next;
	add_argument(*current_cmd, *tokens, T_REDIRECT_OUT);

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
