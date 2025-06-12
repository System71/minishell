/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:55:02 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:03:15 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = ft_xmalloc(sizeof(t_command), 8);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	append_arg_to_command(t_command *cmd, char *arg)
{
	int	count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	cmd->args = ft_realloc(cmd->args, sizeof(char *) *(count),
			sizeof(char *) *(count + 2), 8);
	cmd->args[count] = arg;
	cmd->args[count + 1] = NULL;
}

static t_command	*get_last_command(t_command *cmd_list)
{
	t_command	*tmp;

	tmp = cmd_list;
	while (tmp != NULL && tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

static void	append_command(t_command **cmd_list, t_command *new_cmd)
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

t_command	*init_or_get_current_command(t_command **cmd_list,
						t_command *current_cmd)
{
	t_command	*new_cmd;

	if (current_cmd == NULL)
	{
		new_cmd = create_command();
		append_command(cmd_list, new_cmd);
		return (new_cmd);
	}
	return (current_cmd);
}
