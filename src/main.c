/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/15 09:19:29 by prigaudi         ###   ########.fr       */
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
// CTRL+D : Lors du CTRL+D readline renvoie NULL,
// on doit donc le traiter dans la boucle principale
int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_command	*head;
	t_command	*current;
	char		**my_env;
	char		*line;

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
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*line)
			add_history(line);
		// PROVISOIRE
		if (!ft_strncmp(line, "exit", 5))
			return (0);
		cmd_list = init_test_list(line);
		head = cmd_list;
		current = head;
		// FIN PROVISOIRE
		// INITIALISATION DE LA LISTE CHAINEE A FAIRE ICI
		// Le free(line) avant les return peuvent ils etre fait avant?
		// Il faudra free la liste chainée
		// Comment sait on qu'on a un pipe?
		while (current)
		{
			current->pid = fork();
			if (!current->next && current->pid == 0)
				cmd_process(current, &my_env);
			waitpid(current->pid, current->status, 0);
			current = current->next;
		}
		free(line);
	}
}
