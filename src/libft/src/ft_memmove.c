/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:07:13 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:06:48 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*overlap(unsigned char *mydest, unsigned char *mysrc, size_t c)
{
	size_t	i;

	i = c;
	while (i > 0)
	{
		mydest[i - 1] = mysrc[i - 1];
		i--;
	}
	return (NULL);
}

static void	*notoverlap(unsigned char *mydest, unsigned char *mysrc, size_t c)
{
	size_t	i;

	i = 0;
	while (i < c)
	{
		mydest[i] = mysrc[i];
		i++;
	}
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t c)
{
	unsigned char	*mydest;
	unsigned char	*mysrc;

	mysrc = (unsigned char *)src;
	mydest = (unsigned char *)dest;
	if (c == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	if (mydest > mysrc && mydest < mysrc + c)
		overlap(mydest, mysrc, c);
	else
		notoverlap(mydest, mysrc, c);
	return (dest);
}
