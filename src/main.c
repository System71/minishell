/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 17:35:17 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// VOIR POUR CREER UN PIPE UNIQUEMENT EN CAS DE BESOIN
// UNE COMMANDE SEULE N'A PAS BESOIN PAR EXEMPLE
// cmd_result = -1 si on recoit exit
int	main(int argc, char **argv, char **envp)
{
	t_command	*head;
	t_command	*new1;
	t_command	*new2;
	t_command	*current;
	char		*line;
	int			cmd_result;

	new1 = malloc(sizeof(t_command));
	new2 = malloc(sizeof(t_command));
	(void)argc;
	(void)argv;
	(void)envp;
	signals();
	current = head;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		// INITIALISATION DE LA LISTE CHAINEE A FAIRE ICI
		// Le free(line) avant les return peuvent ils etre fait avant?
		// Il faudra free la liste chainée
		while (current)
		{
			cmd_result = cmd_process(envp, current);
			if (cmd_result == -1 || cmd_result == 1 && current->next == NULL)
			{
				free(line);
				return (1);
			}
			else if (cmd_result == 0 && current->next == NULL)
			{
				free(line);
				return (0);
			}
			else if (cmd_result == 127 && current->next == NULL)
			{
				free(line);
				return (127);
			}
			else
				current = current->next;
		}
		free(line);
	}
}
