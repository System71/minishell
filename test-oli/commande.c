/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:46:34 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/08 12:00:48 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_command *create_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	/*cmd->type = T_UNDEFINED;*/
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->next = NULL;
	return cmd;
}

void add_argument(t_command *cmd, t_token *token, t_token_type type)
{
    if (!cmd)
        return;
    char **new_argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
    if (!new_argv)
        return;
    cmd->argv = new_argv;
	if (cmd->argc == 0)
	{
		cmd->type = type;
	}
	cmd->quote = token->quote;
    cmd->argv[cmd->argc] = strdup(token->content);
    cmd->argc++;
    cmd->argv[cmd->argc] = NULL;
}

/*void print_commands(t_command *cmd_list)*/
/*{*/
/*    int cmd_index = 1;*/
/*	printf("Listes des commandes :\n");*/
/*    for (t_command *cmd = cmd_list; cmd; cmd = cmd->next)*/
/*    {*/
/*        printf("Commande %d: types: %s: Quote: %s\n", cmd_index, token_type_to_string(cmd->type), token_quote_to_string(cmd->quote));*/
/*        for (int i = 0; i < cmd->argc; i++)*/
/*        {*/
/*            printf("  argv[%d] = %s\n", i, cmd->argv[i]);*/
/*        }*/
/*        cmd_index++;*/
/*    }*/
/*}*/

