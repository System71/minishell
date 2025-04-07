/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 18:08:56 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*init_test_list(char *line)
{
	t_command	*new;
	char		**split;
	int			len_split;
	int			i;

	split = ft_split(line, ' ');
	len_split = 0;
	while (split[len_split])
	{
		len_split++;
	}
	new = malloc(sizeof(t_command));
	new->type = T_WORD;
	new->argv = malloc(sizeof(char **) * (len_split + 1));
	new->next = NULL;
	i = 0;
	while (i < len_split)
	{
		new->argv[i] = ft_strdup(split[i]);
		i++;
	}
	new->argv[i] = NULL;
	return (new);
}

// VOIR POUR CREER UN PIPE UNIQUEMENT EN CAS DE BESOIN
// UNE COMMANDE SEULE N'A PAS BESOIN PAR EXEMPLE
// cmd_result = -1 si on recoit exit
int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_command	*head;
	t_command	*current;
	char		**my_env;
	char		*line;
	int			cmd_result;

	(void)argc;
	(void)argv;
	signals();
	my_env = env_cpy(envp);
	if (!my_env)
		exit_failure("env copy crashed");
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		cmd_list = init_test_list(line);
		printf("cmd=%s\n", cmd_list->argv[0]);
		head = cmd_list;
		current = head;
		// !!!! ATTENTION OBlIGATION DE CREE UN FORK POUR POUVOIR EXECUTER LA COMMANDE SANS QUITTER MNISHELL !!!!
		// INITIALISATION DE LA LISTE CHAINEE A FAIRE ICI
		// Le free(line) avant les return peuvent ils etre fait avant?
		// Il faudra free la liste chainée
		while (current)
		{
			cmd_result = cmd_process(current, &my_env);
			if (cmd_result == 1 && current->next == NULL)
			{
				// free(line);
				break ;
				// return (1);
			}
			else if (cmd_result == -1 || (cmd_result == 0
					&& current->next == NULL))
			{
				// free(line);
				break ;
				// return (0);
			}
			else if (cmd_result == 127 && current->next == NULL)
			{
				// free(line);
				break ;
				// return (127);
			}
			else
				current = current->next;
		}
		free(line);
	}
}
