/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:15 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/08 14:07:26 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "lexer.h"

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

    // Lexer
    t_token *tokens = lexer(input);
    if (!tokens)
    {
        fprintf(stderr, "Aucun token généré.\n");
        return EXIT_FAILURE;
    }
		/*printf("Before group\n");*/
    /*print_tokens(tokens);*/
	tokens = group_tokens(tokens);
		printf("\nAfter group\n");
    print_tokens(tokens);
    // À condition d'avoir une fonction print_tokens(...) ou similaire
    // print_tokens(tokens);

    // Parser minimal
    /*t_command *cmd_list = parser(tokens);*/
    /*if (cmd_list)*/
    /*    print_commands(cmd_list);*/
}
    // Penser à libérer la mémoire (tokens et commandes) à la fin
    return EXIT_SUCCESS;
}
