/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/07 16:56:10 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./memory/mem.h"

// static t_command	*init_test_list(char *line)
// {
// 	t_command	*new;
// 	char		**split;
// 	int			len_split;
// 	int			i;

// 	split = ft_split(line, ' ');
// 	len_split = 0;
// 	while (split[len_split])
// 	{
// 		len_split++;
// 	}
// 	new = malloc(sizeof(t_command));
// 	new->type = T_WORD;
// 	new->argv = malloc(sizeof(char **) * (len_split + 1));
// 	new->next = NULL;
// 	i = 0;
// 	while (i < len_split)
// 	{
// 		new->argv[i] = ft_strdup(split[i]);
// 		i++;
// 	}
// 	new->argv[i] = NULL;
// 	return (new);
// }

// VOIR POUR CREER UN PIPE UNIQUEMENT EN CAS DE BESOIN
// UNE COMMANDE SEULE N'A PAS BESOIN PAR EXEMPLE
// cmd_result = -1 si on recoit exit
// CTRL+D : Lors du CTRL+D readline renvoie NULL,
// on doit donc le traiter dans la boucle principale
int	main(int argc, char **argv, char **envp)
// int	main(void)
{
	t_command	*cmd_list;
	t_command	*current;
	char		**my_env;
	char		*input;

	(void)argc;
	(void)argv;
	signals();
	my_env = env_cpy(envp);
	if (!my_env)
		exit_failure("env copy crashed");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*input)
			add_history(input);

		cmd_list = parse_input(input);
		print_commands(cmd_list);
		// Pourquoi redefinir cmd_list a current ? 
		// Il faudra une protection
		// if (cmd_list != NULL)
		// new_pipex(...);
		current = cmd_list;
		new_pipex(current, &my_env);
		free(input);
	}
	mem_free_all();
}
