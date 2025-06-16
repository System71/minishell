/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing_return.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:35:12 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 13:36:36 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	report_syntax_error(t_syntax_err err, const char *input)
{
	if (err == ERR_UNCLOSED_QUOTE)
		printf("syntax error: unclosed quote \n");
	else if (err == ERR_LINE_CONTINUATION)
		printf("syntax error: unexpected end of line (\\) in `%s`\n", input);
	else if (err == ERR_BONUS)
		printf("syntax error near unexpected token `%s`\n", input);
	else if (err == ERR_PIPE_AT_EDGE)
		printf("syntax error near unexpected token `|`\n");
	else if (err == ERR_CONSECUTIVE_PIPES)
		printf("syntax error near unexpected token `|`\n");
	else if (err == ERR_ISOLATED_OP)
		printf("syntax error near unexpected token `%s`\n", input);
	else if (err == ERR_MISSING_FILENAME)
		printf("syntax error near unexpected token `%s`\n", input);
	else if (err == ERR_INVALID_SEQUENCE)
		printf("syntax error near invalid token sequence\n");
}
