/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:15 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/16 08:58:19 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"


int main(void)
{
	char *input;
	while (1)
	{
		input = readline("minishell> "); 
		if (!input)
		{
			fprintf(stderr, "Erreur de lecture de l'entrée.\n");
			return EXIT_FAILURE;
		}
		// Ajoute l'entrée à l'historique si non vide
		if (input[0] != '\0')
			add_history(input);
		// Suppression du \n
		input[strcspn(input, "\n")] = '\0';

		printf("################################################\n");
		t_token *tokens = lexer(input);
		printf("Before group\n");
		print_tokens(tokens);

		printf("################################################\n");
		tokens = group_tokens(tokens);
		printf("\nAfter group\n");
		print_tokens(tokens);

		printf("################################################\n");
		heredoc_handle(tokens);
		printf("Here_doc\n");
		print_tokens(tokens);

		printf("################################################\n");
		expand_handle(tokens);
		printf("Expand\n");
		print_tokens(tokens);

		printf("################################################\n");
		t_command *cmd_list = parse_commands(tokens);
		print_commands(cmd_list);
	}
	// Penser à libérer la mémoire (tokens et commandes) à la fin
	return EXIT_SUCCESS;
}
