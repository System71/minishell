/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:56:54 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 14:18:24 by okientzl         ###   ########.fr       */
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
    cmd->argc = 0;
    cmd->argv = NULL;
    cmd->next = NULL;
    return cmd;
}

void add_argument(t_command *cmd, const char *arg)
{
    if (!cmd)
        return;
    char **new_argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
    if (!new_argv)
        return;
    cmd->argv = new_argv;
    cmd->argv[cmd->argc] = strdup(arg);
    cmd->argc++;
    cmd->argv[cmd->argc] = NULL;
}

void print_commands(t_command *cmd_list)
{
    int cmd_index = 1;
    for (t_command *cmd = cmd_list; cmd; cmd = cmd->next)
    {
        printf("Commande %d:\n", cmd_index);
        for (int i = 0; i < cmd->argc; i++)
        {
            printf("  argv[%d] = %s\n", i, cmd->argv[i]);
        }
        cmd_index++;
    }
}

