/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/25 11:44:26 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../includes/parser.h"

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

/*t_command *parse_commands(t_token *tokens)*/
/*{*/
/*    t_command *cmd_list = NULL;   // Pointeur vers la tête de la liste des commandes*/
/*    t_command *current_cmd = NULL;*/
/**/
/*    while (tokens)*/
/*    {*/
/*        // Si le token est un séparateur de pipe, on passe à la commande suivante.*/
/*        if (tokens->type == T_PIPE)*/
/*        {*/
/*            current_cmd = NULL;*/
/*            tokens = tokens->next;*/
/*            continue;*/
/*        }*/
/**/
/*        // S'il n'y a pas de commande en cours, on en crée une nouvelle.*/
/*        if (!current_cmd)*/
/*        {*/
/*            t_command *new_cmd = create_command();*/
/*            if (!cmd_list)*/
/*                cmd_list = new_cmd;*/
/*            else*/
/*            {*/
/*                t_command *tmp = cmd_list;*/
/*                while (tmp->next)*/
/*                    tmp = tmp->next;*/
/*                tmp->next = new_cmd;*/
/*            }*/
/*            current_cmd = new_cmd;*/
/*        }*/
/**/
/*        // Pour un token de type T_WORD, on crée un argument distinct sans fusionner*/
/*        if (tokens->type == T_WORD)*/
/*        {*/
/*            char *arg = concat_segments(tokens);*/
/*            append_arg_to_command(current_cmd, arg);*/
/*        }*/
/*        // Traitement des redirections*/
/*        else if (tokens->type == T_REDIRECT_IN || tokens->type == T_REDIRECT_OUT ||*/
/*                 tokens->type == T_APPEND    || tokens->type == T_HEREDOC)*/
/*        {*/
/*            t_redirection *redir = malloc(sizeof(t_redirection));*/
/*            if (!redir)*/
/*            {*/
/*                perror("malloc");*/
/*                exit(EXIT_FAILURE);*/
/*            }*/
/*            // Pour un heredoc, on force le type à REDIRECT_IN*/
/*            if (tokens->type == T_HEREDOC)*/
/*                redir->type = T_REDIRECT_IN;*/
/*            else*/
/*                redir->type = tokens->type;*/
/*            redir->next = NULL;*/
/**/
/*            if (tokens->type == T_HEREDOC)*/
/*            {*/
/*                // Génère le nom du fichier temporaire, écrit le contenu dans le fichier,*/
/*                // et stocke le nom dans redir->target.*/
/*                char *temp_filename = generate_temp_filename();*/
/*                FILE *fp = fopen(temp_filename, "w");*/
/*                if (!fp)*/
/*                {*/
/*                    perror("fopen");*/
/*                    exit(EXIT_FAILURE);*/
/*                }*/
/*                // Le contenu du heredoc se trouve dans le premier segment du token.*/
/*                fputs(tokens->segments->content, fp);*/
/*                fclose(fp);*/
/*                redir->target = strdup(temp_filename);*/
/*                free(temp_filename);*/
/*            }*/
/*            else*/
/*            {*/
/*                // Pour les autres redirections, la cible est obtenue en concaténant les segments.*/
/*                redir->target = concat_segments(tokens);*/
/*            }*/
/*            // Ajoute la redirection à la commande courante.*/
/*            if (!current_cmd->redirs)*/
/*                current_cmd->redirs = redir;*/
/*            else*/
/*            {*/
/*                t_redirection *r = current_cmd->redirs;*/
/*                while (r->next)*/
/*                    r = r->next;*/
/*                r->next = redir;*/
/*            }*/
/*        }*/
/**/
/*        tokens = tokens->next;*/
/*    }*/
/**/
/*    return cmd_list;*/
/*}*/
// Récupère le dernier élément d’une liste de commandes
static t_command  *get_last_command(t_command *cmd_list)
{
    t_command  *tmp;

    tmp = cmd_list;
    while (tmp != NULL && tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    return (tmp);
}

// Ajoute une commande à la fin de la liste
static void  append_command(t_command **cmd_list, t_command *new_cmd)
{
    if (*cmd_list == NULL)
    {
        *cmd_list = new_cmd;
    }
    else
    {
        get_last_command(*cmd_list)->next = new_cmd;
    }
}

// Initialise ou renvoie la commande courante
static t_command  *init_or_get_current_command(t_command **cmd_list,
                                               t_command  *current_cmd)
{
    if (current_cmd == NULL)
    {
        t_command  *new_cmd;

        new_cmd = create_command();
        append_command(cmd_list, new_cmd);
        return (new_cmd);
    }
    return (current_cmd);
}

// Traite un token WORD : concatène ses segments et l’ajoute aux args
static void  process_word_token(t_token *tok, t_command *current_cmd)
{
    char  *arg;

    arg = concat_segments(tok);
    append_arg_to_command(current_cmd, arg);
}

// Construit une structure t_redirection à partir du token
static t_redirection  *build_redirection(t_token *tok)
{
    t_redirection  *redir;
    char           *temp_filename;
    FILE           *fp;

    redir = malloc(sizeof(*redir));
    if (redir == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (tok->type == T_HEREDOC)
    {
        temp_filename = generate_temp_filename();
        fp            = fopen(temp_filename, "w");
        if (fp == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fputs(tok->segments->content, fp);
        fclose(fp);
        redir->target = strdup(temp_filename);
        free(temp_filename);
        redir->type   = T_REDIRECT_IN;
    }
    else
    {
        redir->target = concat_segments(tok);
        redir->type   = tok->type;
    }
    redir->next = NULL;
    return (redir);
}

// Ajoute la redirection à la commande courante
static void  process_redirection_token(t_token *tok,
                                       t_command *current_cmd)
{
    t_redirection  *redir;
    t_redirection  *last;

    redir = build_redirection(tok);
    if (current_cmd->redirs == NULL)
    {
        current_cmd->redirs = redir;
    }
    else
    {
        last = current_cmd->redirs;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = redir;
    }
}

// Fonction principale qui boucle sur les tokens et construit la liste
t_command  *parse_commands(t_token *tokens)
{
    t_command  *cmd_list;
    t_command  *current_cmd;

    cmd_list     = NULL;
    current_cmd  = NULL;
    while (tokens != NULL)
    {
        if (tokens->type == T_PIPE)
        {
            current_cmd = NULL;
        }
        else
        {
            current_cmd = init_or_get_current_command(&cmd_list,
                                                      current_cmd);
            if (tokens->type == T_WORD)
            {
                process_word_token(tokens, current_cmd);
            }
            else if (is_redirection_type(tokens->type))
            {
                process_redirection_token(tokens, current_cmd);
            }
        }
        tokens = tokens->next;
    }
    return (cmd_list);
}

