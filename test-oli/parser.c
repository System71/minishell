/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:36:31 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 14:36:31 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

/*
** Implémentation d'un parser minimal
**
** Le parser transforme la liste des tokens en une liste de commandes.
** Ici, on considère que les tokens de type T_WORD, T_SINGLE_QUOTE et T_DOUBLE_QUOTE
** correspondent aux arguments d'une commande. Le token PIPE indique la séparation
** entre commandes.
*/
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
        
        if (tokens->type == T_WORD ||
            tokens->type == T_SINGLE_QUOTE ||
            tokens->type == T_DOUBLE_QUOTE)
        {
            add_argument(current_cmd, tokens->content);
        }
        else if (tokens->type == T_PIPE)
        {
            current_cmd->next = create_command();
            current_cmd = current_cmd->next;
        }
        // Vous pouvez ajouter ici la gestion d'autres tokens (redirections, etc.)
        tokens = tokens->next;
    }
    return head;
}



