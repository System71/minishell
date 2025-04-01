/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:19:14 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 14:27:53 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// Fonction interne pour déterminer le type du token selon son contenu.
t_token_type get_token_type(const char *str)
{
    if (strcmp(str, "|") == 0)
        return T_PIPE;
    else if (strcmp(str, "<") == 0)
        return T_REDIRECT_IN;
    else if (strcmp(str, ">") == 0)
        return T_REDIRECT_OUT;
    else if (strcmp(str, ">>") == 0)
        return T_APPEND;
    else if (strcmp(str, "<<") == 0)
        return T_HEREDOC;
    return T_WORD;
}

t_token *create_empty_token_list(void)
{
    return NULL;
}

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '$');
}

t_token *add_token(t_token *list, const char *content)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return list; // En cas d'erreur, retourne la liste existante.
    new_token->type = get_token_type(content);
    new_token->content = strdup(content);
    new_token->next = NULL;
    
    if (!list)
        return new_token;
    t_token *tmp = list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_token;
    return list;
}

void flush_buffer(char *buffer, int *buf_index, t_token **tokens)
{
    if (*buf_index > 0)
    {
        buffer[*buf_index] = '\0';
        *tokens = add_token(*tokens, buffer);
        *buf_index = 0;
        memset(buffer, 0, BUFFER_SIZE);
    }
}

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case T_WORD:          return "T_WORD";
        case T_SINGLE_QUOTE:  return "T_SINGLE_QUOTE";
        case T_DOUBLE_QUOTE:  return "T_DOUBLE_QUOTE";
        case T_REDIRECT_IN:   return "T_REDIRECT_IN";
        case T_REDIRECT_OUT:  return "T_REDIRECT_OUT";
        case T_APPEND:        return "T_APPEND";
        case T_HEREDOC:       return "T_HEREDOC";
        case T_PIPE:          return "T_PIPE";
        case T_DOLLAR:        return "T_DOLLAR";
        default:              return "UNKNOWN";
    }
}

void print_tokens(t_token *tokens)
{
    printf("Liste des tokens générés:\n");
    for (t_token *tmp = tokens; tmp != NULL; tmp = tmp->next)
    {
        printf("Type: %d (%s), Contenu: %s\n",
               tmp->type, token_type_to_string(tmp->type), tmp->content);
    }
}
