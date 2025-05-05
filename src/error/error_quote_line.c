/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:35:12 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/05 09:35:12 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include <stdio.h>

void report_syntax_error(t_syntax_err err, const char *input)
{
    switch (err) {
    case ERR_UNCLOSED_QUOTE:
        fprintf(stderr, "minishell: syntax error: unclosed quote in `%s`\n", input);
        break;
    case ERR_LINE_CONTINUATION:
        fprintf(stderr, "minishell: syntax error: unexpected end of line (\\) in `%s`\n", input);
        break;
    default:
        break;
    }
}

