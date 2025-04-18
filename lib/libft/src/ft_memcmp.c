/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:55:52 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:20:01 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *first, const void *second, size_t n)
{
	size_t			i;
	unsigned char	*myfirst;
	unsigned char	*mysecond;

	myfirst = (unsigned char *)first;
	mysecond = (unsigned char *)second;
	i = 0;
	while (i < n)
	{
		if (myfirst[i] != mysecond[i])
			return (myfirst[i] - mysecond[i]);
		i++;
	}
	return (0);
}
