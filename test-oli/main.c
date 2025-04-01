/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:30:58 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/01 14:35:48 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

int main(void)
{
    char input[BUFFER_SIZE];

    printf("minishell> ");
    if (!fgets(input, BUFFER_SIZE, stdin))
    {
        fprintf(stderr, "Erreur de lecture de l'entrée.\n");
        return EXIT_FAILURE;
    }
    // Suppression du \n
    input[strcspn(input, "\n")] = '\0';

    // Lexer
    t_token *tokens = lexer(input);
    if (!tokens)
    {
        fprintf(stderr, "Aucun token généré.\n");
        return EXIT_FAILURE;
    }

    // Affichage des tokens (debug)
    print_tokens(tokens);
    // À condition d'avoir une fonction print_tokens(...) ou similaire
    // print_tokens(tokens);

    // Parser minimal
    t_command *cmd_list = parser(tokens);

    // Affichage pour vérifier
    if (cmd_list)
        print_commands(cmd_list);

    // Penser à libérer la mémoire (tokens et commandes) à la fin
    return EXIT_SUCCESS;
}
