/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_temp_filename.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:42:34 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 11:56:04 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/parse_tempfile.h"
#include "../memory/mem.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static int	read_urandom(void *buf, size_t n)
{
	int	fd;
	int	status;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	status = read(fd, buf, n);
	close(fd);
	if (status != (int)n)
		return (-1);
	return (0);
}

static void	fill_hex(unsigned char *rnd, char *hex)
{
	static const char	*digits;
	int					i;
	unsigned char		byte;
	int					pos;

	digits = "0123456789abcdef";
	i = 0;
	while (i < RANDOM_BYTES)
	{
		byte = rnd[i];
		pos = 2 * i;
		hex[pos] = digits[(byte >> 4) & 0x0F];
		hex[pos + 1] = digits[byte & 0x0F];
		i++;
	}
	hex[2 * RANDOM_BYTES] = '\0';
}

static void	build_filename(char *dst,
						const char *base,
						const char *hexpart)
{
	size_t	bi;
	size_t	hi;

	bi = 0;
	while (base[bi] != '\0')
	{
		dst[bi] = base[bi];
		bi++;
	}
	hi = 0;
	while (hexpart[hi] != '\0')
	{
		dst[bi + hi] = hexpart[hi];
		hi++;
	}
	dst[bi + hi] = '\0';
}

char	*generate_temp_filename(void)
{
	t_tempfile	tf;
	int			status;

	tf.filename = ft_xmalloc(BUF_SIZE);
	tf.tries = 0;
	while (tf.tries < MAX_TRY)
	{
		tf.tries++;
		status = read_urandom(tf.rnd, RANDOM_BYTES);
		if (status != 0)
			break ;
		fill_hex(tf.rnd, tf.hexpart);
		build_filename(tf.filename, BASE, tf.hexpart);
		tf.fd = open(tf.filename, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (tf.fd >= 0)
		{
			close(tf.fd);
			return (tf.filename);
		}
		if (errno != EEXIST)
			break ;
	}
	return (NULL);
}
