/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:53:33 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:35:15 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recurs(char **str, long int number, int *i)
{
	if (number < 0)
	{
		(*str)[*i] = '-';
		number = -number;
		(*i)++;
	}
	if (number >= 0 && number <= 9)
	{
		(*str)[*i] = number + 48;
		(*i)++;
	}
	else
	{
		recurs(&*str, number / 10, &*i);
		(*str)[*i] = number % 10 + 48;
		(*i)++;
	}
}

static int	length(long int number)
{
	long int	len;
	long int	i;

	len = 0;
	if (number < 0)
	{
		len++;
		number = -number;
	}
	if (number >= 0 && number <= 9)
	{
		len++;
		return (len);
	}
	i = number;
	while (i >= 1)
	{
		len++;
		i = i / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			i;
	long int	number;

	number = (long int)n;
	len = length(number);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	recurs(&str, number, &i);
	str[i] = '\0';
	return (str);
}
