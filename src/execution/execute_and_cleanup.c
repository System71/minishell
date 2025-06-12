/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:48:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:26:12 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	execute_and_cleanup(t_command *cmd_list, t_env *my_env)
{
	exec_pipeline(cmd_list, my_env);
	destroy_file_heredoc(cmd_list);
}
