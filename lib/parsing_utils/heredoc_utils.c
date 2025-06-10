/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:13:05 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 08:18:20 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	destroy_file_heredoc(t_command *cmd_list)
{
	while (cmd_list)
	{
		while (cmd_list->redirs)
		{
			if (cmd_list->redirs->type == T_HEREDOC)
			{
				if (unlink(cmd_list->redirs->target) == -1)
					perror("unlink failed");
			}
			cmd_list->redirs = cmd_list->redirs->next;
		}
		cmd_list = cmd_list->next;
	}
}
