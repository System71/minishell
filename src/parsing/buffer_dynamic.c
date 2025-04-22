/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_dynamic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:25:36 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/22 07:59:05 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"

t_dynamic_buffer	*init_dynamic_buffer(void)
{
	t_dynamic_buffer	*buf;

	buf = malloc(sizeof(t_dynamic_buffer));
	if (!buf)
		return (NULL);
	buf->capacity = INITIAL_BUFFER_SIZE;
	buf->len = 0;
	buf->data = malloc(buf->capacity);
	if (!buf->data)
	{
		free(buf);
		return (NULL);
	}
	buf->data[0] = '\0';
	return (buf);
}

void	free_dynamic_buffer(t_dynamic_buffer *buf)
{
	if (buf)
	{
		free(buf->data);
		free(buf);
	}
}
