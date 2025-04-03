/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:18:04 by prigaudi          #+#    #+#             */
/*   Updated: 2025/02/10 19:21:14 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_index(char *buffer, int *stop_read)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			*stop_read = 1;
			break ;
		}
		i++;
	}
	return (i);
}

static int	get_buffer(char **line, char *buffer)
{
	int	i;
	int	stop_read;

	i = 0;
	stop_read = 0;
	if (buffer[0])
	{
		i = find_index(buffer, &stop_read);
		if (stop_read == 1)
		{
			*line = ft_strnjoin(*line, buffer, i);
			if (!*line)
				return (0);
			ft_memmove(buffer, buffer + i, BUFFER_SIZE + 1 - i);
			return (1);
		}
		*line = ft_strnjoin(*line, buffer, i);
		if (!*line)
			return (0);
	}
	return (2);
}

static int	read_buffer(char **line, ssize_t *byte_read, char *buffer, int fd)
{
	*byte_read = read(fd, buffer, BUFFER_SIZE);
	if (*byte_read == -1)
	{
		buffer[0] = '\0';
		free(*line);
		return (0);
	}
	if (*byte_read == 0)
	{
		if (line)
		{
			buffer[0] = '\0';
			return (1);
		}
		return (0);
	}
	buffer[*byte_read] = '\0';
	return (2);
}

static char	*get_line(char *buffer, int fd)
{
	char	*line;
	int		check;
	ssize_t	byte_read;

	line = NULL;
	byte_read = 1;
	check = get_buffer(&line, buffer);
	if (check == 0)
		return (NULL);
	if (check == 1)
		return (line);
	while (byte_read)
	{
		check = read_buffer(&line, &byte_read, buffer, fd);
		if (check == 0)
			return (NULL);
		if (check == 1)
			return (line);
		check = get_buffer(&line, buffer);
		if (check == 0)
			return (NULL);
		if (check == 1)
			return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(buffer, fd);
	return (line);
}
