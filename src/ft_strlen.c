/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:14:59 by okientzl          #+#    #+#             */
/*   Updated: 2025/02/27 17:14:59 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/lib_utils.h"
#include <unistd.h>
/***** ft_strlen *****/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
	{
		write(2, "Erreur : pointer NULL ft_strlen\n", 32);
		return (0);
	}
	i = 0;
	while (s[i])
		i++;
	return (i);
}
