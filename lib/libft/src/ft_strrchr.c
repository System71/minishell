/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:11:42 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:15:33 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*tamp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	tamp = NULL;
	while (i <= len)
	{
		if (str[i] == (unsigned char)c)
			tamp = (char *)&str[i];
		i++;
	}
	return (tamp);
}
