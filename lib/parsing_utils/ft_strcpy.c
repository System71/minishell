/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:28:57 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:28:57 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
