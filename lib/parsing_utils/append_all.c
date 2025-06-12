/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:43:15 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:28:23 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_str(char **dest, const char *src)
{
	char	*new_str;
	size_t	old_len;
	size_t	src_len;

	old_len = 0;
	if (*dest)
		old_len = ft_strlen(*dest);
	src_len = ft_strlen(src);
	new_str = ft_realloc(*dest, old_len, old_len + src_len + 1, 8);
	if (!new_str)
	{
		free(*dest);
		return (1);
	}
	ft_memcpy(new_str + old_len, src, src_len);
	new_str[old_len + src_len] = '\0';
	*dest = new_str;
	return (0);
}

int	append_char(t_dynamic_buffer *buf, char c)
{
	size_t	new_capacity;
	char	*new_data;

	if (buf->len + 1 >= buf->capacity)
	{
		new_capacity = buf->capacity * 2;
		new_data = ft_realloc(buf->data, buf->capacity, new_capacity, 8);
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
