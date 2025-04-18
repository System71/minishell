/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:23:31 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:04:58 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t c)
{
	unsigned char	*mydest;
	unsigned char	*mysrc;
	size_t			i;

	mysrc = (unsigned char *)src;
	mydest = (unsigned char *)dest;
	if (c == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < c)
	{
		mydest[i] = mysrc[i];
		i++;
	}
	return (dest);
}
