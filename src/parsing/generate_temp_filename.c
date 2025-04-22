/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_temp_filename.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:42:34 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/22 09:16:50 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../includes/lib_utils.h"
#include "../../includes/types.h"

#define MAX_TRY		10000
#define BUF_SIZE	256
#define BASE		"/tmp/heredoc_"

int	ft_itoa_rev(int n, char *buf)
{
	char			tmp[12];
	size_t			i;
	size_t			len;
	unsigned int	un;

	un = (unsigned int)n;
	i = 0;
	if (un == 0)
		tmp[i++] = '0';
	while (un > 0)
	{
		tmp[i] = '0' + (un % 10);
		i++;
		un /= 10;
	}
	len = i;
	while (len > 0)
	{
		len--;
		*buf = tmp[len];
		buf++;
	}
	*buf = '\0';
	return ((int)i);
}

char	*generate_temp_filename(void)
{
	t_tempfile	tmp;

	tmp.filename = malloc(BUF_SIZE);
	if (!tmp.filename)
		return (NULL);
	tmp.counter = 0;
	while (tmp.counter++ < MAX_TRY)
	{
		ft_strcpy(tmp.filename, BASE);
		tmp.len = ft_itoa_rev(tmp.counter, tmp.filename + ft_strlen(BASE));
		if (tmp.len < 0)
		{
			free(tmp.filename);
			return (NULL);
		}
		tmp.fd = open(tmp.filename, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (tmp.fd != -1)
		{
			close(tmp.fd);
			return (tmp.filename);
		}
	}
	free(tmp.filename);
	return (NULL);
}
