/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_dynamic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:25:36 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/16 07:54:46 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
#include "includes/lib_utils.h"

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

int	append_char(t_dynamic_buffer *buf, char c)
{
	size_t	new_capacity;
	char	*new_data;

	if (buf->len + 1 >= buf->capacity)
	{
		new_capacity = buf->capacity * 2;
		new_data = ft_realloc(buf->data, buf->capacity, new_capacity);
		if (!new_data)
			return (0);
		buf->data = new_data;
		buf->capacity = new_capacity;
	}
	buf->data[buf->len] = c;
	buf->len++;
	buf->data[buf->len] = '\0';
	return (1);
}

void	free_dynamic_buffer(t_dynamic_buffer *buf)
{
	if (buf)
	{
		free(buf->data);
		free(buf);
	}
}
