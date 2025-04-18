/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:31:44 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/28 16:52:51 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_string(char *s)
{
	int	counter;
	int	isneg;

	counter = 0;
	isneg = 0;
	if (s == NULL)
		return (ft_string("(null)"));
	while (s[counter] != '\0')
	{
		isneg = write(1, &s[counter], 1);
		if (isneg == -1)
			return (-1);
		else
		{
			counter++;
		}
	}
	return (counter);
}
