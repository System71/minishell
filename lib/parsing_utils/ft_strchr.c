/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:25:43 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/30 14:40:22 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lib_utils.h"
#include <unistd.h>
/***** ft_strchr *****/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
	{
		write(2, "Error : pointer NULL in ft_strchr\n", 34);
		return (NULL);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
