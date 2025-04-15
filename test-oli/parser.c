/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/15 14:31:17 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
// // --- Fonctions Helpers --- //
// Concatène tous les segments d'un token en une seule chaîne.
// On parcourt la liste chaînée des segments et on les concatène.
static char *concat_segments(t_token *token)
{
	size_t total_len = 0;
	t_token_segment *seg = token->segments;
	while (seg)
	{
		total_len += strlen(seg->content);
		seg = seg->next;
	}
	char *result = malloc(total_len + 1);
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	result[0] = '\0';
	seg = token->segments;
	while (seg)
	{
		strcat(result, seg->content);
		seg = seg->next;
	}
	return result;
}
// Crée un nouveau nœud de commande et l'initialise.
static t_command *create_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->args = NULL;
	// Tableau d'arguments initial vide
	cmd->redirs = NULL;
	// Pas de redirections au départ
	cmd->next = NULL;
	return cmd;
}
// Ajoute un argument à la commande courante.
// On alloue dynamiquement (en gardant un tableau NULL-terminé).
static void append_arg_to_command(t_command *cmd, char *arg)
{
	int count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	cmd->args = realloc(cmd->args, sizeof(char *) * (count + 2));
	if (!cmd->args)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	cmd->args[count] = arg;
	cmd->args[count + 1] = NULL;
}
// // --- Fonction de Parsing Final --- //
t_command *parse_commands(t_token *tokens)
{
	t_command *cmd_list = NULL;	// Pointeur vers la tête de la liste de commandes
	t_command *current_cmd = NULL;
	while (tokens)
	{
		// Si le token est un séparateur de pipe, on passe à la commande suivante.
		if (tokens->type == T_PIPE)
		{
			// On réinitialise la commande courante pour forcer la création d'un nouveau nœud.
			current_cmd = NULL;
			tokens = tokens->next;
			continue;
		}

		// Si pas de commande en cours, on en crée une nouvelle et on l'ajoute à la liste.
		if (!current_cmd)
		{
			t_command *new_cmd = create_command();
			if (!cmd_list)
			{
				cmd_list = new_cmd;
			}
			else
		{
				t_command *tmp = cmd_list;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_cmd;
			}
			current_cmd = new_cmd;
		}

		// Traitement des tokens de type T_WORD :
        // On fusionne tous les tokens T_WORD consécutifs dans un seul argument.
        if (tokens->type == T_WORD)
        {
            // Commence par récupérer le contenu du premier token.
            char *merged_arg = concat_segments(tokens);
            t_token *tmp = tokens->next;
            // Tant que les tokens suivants sont de type T_WORD, on les fusionne.
            while (tmp && tmp->type == T_WORD)
            {
                char *temp_seg = concat_segments(tmp);
                char *old = merged_arg;
                // Ici, on insère un espace entre les parties. Vous pouvez enlever " " si vous préférez une concaténation directe.
                merged_arg = malloc(strlen(old) + strlen(temp_seg) + 2);
                if (!merged_arg)
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                sprintf(merged_arg, "%s %s", old, temp_seg);
                free(old);
                free(temp_seg);
                tokens = tmp;
                tmp = tokens->next;
            }
            append_arg_to_command(current_cmd, merged_arg);
        }		else if (tokens->type == T_REDIRECT_IN || tokens->type == T_REDIRECT_OUT ||
			tokens->type == T_APPEND    || tokens->type == T_HEREDOC)
		{
			// Crée un nœud redirection.
			t_redirection *redir = malloc(sizeof(t_redirection));
			if (!redir)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			if (tokens->type == T_HEREDOC)
				redir->type = T_REDIRECT_IN;
			else
				redir->type = tokens->type;
			redir->next = NULL;

			if (tokens->type == T_HEREDOC)
			{
				// Pour le heredoc : générer le nom du fichier temporaire, l'ouvrir, y écrire le contenu,
				// et stocker le nom dans target.
				char *temp_filename = generate_temp_filename();
				FILE *fp = fopen(temp_filename, "w");
				if (!fp)
				{
					perror("fopen");
					exit(EXIT_FAILURE);
				}
				// Le contenu du heredoc est dans le premier segment du token.
				fputs(tokens->segments->content, fp);
				fclose(fp);
				redir->target = strdup(temp_filename);
				free(temp_filename);
			}
			else
			{
				// Pour les redirections classiques, la cible est la concaténation des segments.
				redir->target = concat_segments(tokens);
			}

			// Ajoute la redirection à la liste des redirections de la commande courante.
			if (!current_cmd->redirs)
				current_cmd->redirs = redir;
			else
			{
				t_redirection *r = current_cmd->redirs;
				while (r->next)
					r = r->next;
				r->next = redir;
			}
		}
		// Passe au token suivant.
		tokens = tokens->next;
	}

	return cmd_list;
}
