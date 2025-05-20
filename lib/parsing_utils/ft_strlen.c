/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:29:38 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:29:38 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/parsing_utils.h"
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
