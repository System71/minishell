/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 10:42:38 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_quote_to_string(t_quote_type quote)
{
	switch (quote)
	{
		case QUOTE_NONE:	  return "None";
		case QUOTE_SINGLE:	  return "Single";
		case QUOTE_DOUBLE:	  return "Double";
	}
}

const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case T_WORD:          return "Word";
        case T_REDIRECT_IN:   return "Redirect_In";
        case T_REDIRECT_OUT:  return "Redirect_Out";
        case T_APPEND:        return "Append";
        case T_HEREDOC:       return "Heredoc";
        case T_PIPE:          return "Pipe";
        case T_OR:            return "Or";         // ||
        case T_AND:           return "And";        // &&
        case T_LPAREN:        return "LParen";     // (
        case T_RPAREN:        return "RParen";     // )
        case T_SEMI:          return "Semicolon";  // ;
        case T_BG:            return "Background"; // &
        default:              return "UNKNOWN";
    }
}


const char	*is_expand_to_string(bool expand)
{
	if (expand == true)
		return ("True");
	else
		return ("False");
}
void	print_tokens(t_token *tokens)
{
	int	token_num;

	token_num= 1;
	while (tokens)
	{
		printf("----------------------------------------------------------------------\n");
		printf("Token %d: Type: %s\n", token_num, token_type_to_string(tokens->type));
		t_token_segment *seg = tokens->segments;
		int seg_num = 1;
		while (seg)
		{
			printf("  Segment %d| Quote: %s, Is_expand:%s Content: \"%s\"\n",
		  seg_num, token_quote_to_string(seg->quote), is_expand_to_string(seg->is_expand), seg->content);
			seg = seg->next;
			seg_num++;
		}
		printf("----------------------------------------------------------------------\n");
		tokens = tokens->next;
		token_num++;
	}
}

static const char	*get_redir_type_str(int type) {
	switch (type) {
		case T_REDIRECT_IN:
			return "REDIRECT_IN (<)";
		case T_REDIRECT_OUT:
			return "REDIRECT_OUT (>)";
		case T_APPEND:
			return "APPEND (>>)";
		case T_HEREDOC:
			return "HEREDOC (<<)";
		default:
			return "UNKNOWN";
	}
}

void	print_commands(t_command *cmd_list)
{
	int cmd_index = 0;
	while (cmd_list)
	{
		printf("Commande #%d:\n", cmd_index);
		if (cmd_list->args)
		{
			printf("  Arguments:\n");
			for (int i = 0; cmd_list->args[i] != NULL; i++) {
				printf("    [%d] %s\n", i, cmd_list->args[i]);
			}
		} else
		{
			printf("  (Aucun argument)\n");
		}

		// Affichage des redirections
		if (cmd_list->redirs) {
			printf("  Redirections:\n");
			t_redirection *redir = cmd_list->redirs;
			while (redir) {
				printf("    Type: %s, Cible: %s\n", get_redir_type_str(redir->type), redir->target);
				redir = redir->next;
			}
		} else {
			printf("  (Aucune redirection)\n");
		}

		printf("\n");
		cmd_list = cmd_list->next;
		cmd_index++;
	}
}
