/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:34:51 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:19:04 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*mystr;

	mystr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (mystr[i] == (unsigned char)c)
			return (&mystr[i]);
		i++;
	}
	return (NULL);
}
