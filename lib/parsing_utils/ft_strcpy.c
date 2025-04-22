/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:28:57 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/22 09:22:33 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

/***** ft_strcpy *****/
int	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (!dst || !src)
	{
		write(2, "Error : pointer NULL in ft_strlcpy\n", 35);
		return (0);
	}
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
