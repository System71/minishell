/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/11 09:40:33 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	manage_redirect_in(t_token **tokens, t_command **current_cmd);
void	manage_pipe(t_token **tokens, t_command **current_cmd);
void	manage_redirect_out(t_token **tokens, t_command **current_cmd);

t_command *parser(t_token *tokens)
{
	t_command *head = NULL;
	t_command *current_cmd = NULL;

	while (tokens)
	{
		if (!head)
		{
			head = create_command();
			current_cmd = head;
		}

		else if (tokens->type == T_WORD ||
			tokens->type == LEXER_SINGLE_QUOTE ||
			tokens->type == LEXER_DOUBLE_QUOTE )
		{
			/*printf("HERE\n");*/
//			if (tokens->content == echo) gerer differement
			add_argument(current_cmd, tokens, tokens->type);
		}
		else if (tokens->type == T_PIPE)
		{
			manage_pipe(&tokens, &current_cmd);
		}
		else if (tokens->type == T_REDIRECT_IN)
		{
			manage_redirect_in(&tokens, &current_cmd);
		}
		else if (tokens->type == T_REDIRECT_OUT )
		{
			manage_redirect_out(&tokens, &current_cmd);
		}
		tokens = tokens->next;
	}
	return head;
}
void	manage_pipe(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not cmd after <\n");
		return;
	}
	*tokens = (*tokens)->next;	
	(*current_cmd)->next = create_command();
    *current_cmd = (*current_cmd)->next;
	add_argument(*current_cmd, *tokens, T_PIPE);
}
void	manage_redirect_in(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not name of file after <\n");
		return;
	}
	*tokens = (*tokens)->next;
	add_argument(*current_cmd, *tokens, T_REDIRECT_IN);
    if ((*tokens)->next != NULL)
    {
		printf("WOW\n");
        (*current_cmd)->next = create_command();
        *current_cmd = (*current_cmd)->next;
    }	
}
void	manage_redirect_out(t_token **tokens, t_command **current_cmd)
{
	if ((*tokens)->next == NULL )
	{
		printf("Synthax error, is empty after <\n");
		return;
	}
	if ((*tokens)->next->type != T_WORD)
	{
		printf("Synthax error, it's not name of file after <\n");
		return;
	}
	*tokens = (*tokens)->next;
	add_argument(*current_cmd, *tokens, T_REDIRECT_OUT);
	if ((*tokens)->next != NULL)
    {
        (*current_cmd)->next = create_command();
        *current_cmd = (*current_cmd)->next;
    }
}


