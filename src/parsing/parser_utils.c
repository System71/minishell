/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:48:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/20 14:52:51 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_or_unset(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	return (!ft_strcmp(cmd->args[0], "export")
		|| !ft_strcmp(cmd->args[0], "unset"));
}

void	process_export_unset_token(t_token *tok, t_command *current_cmd)
{
	char	*full;

	full = concat_segments(tok);
	append_arg_to_command(current_cmd, full);
}

void	process_normal_token(t_token *tok, t_command *current_cmd)
{
	char	*full;

	full = concat_segments(tok);
	append_arg_to_command(current_cmd, full);
}
