/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:23:10 by prigaudi          #+#    #+#             */
/*   Updated: 2024/12/02 09:30:32 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int	counter;
	int	isneg;

	isneg = 0;
	counter = 0;
	if (nbr >= ft_strlen(base))
	{
		isneg = ft_putnbr_base(nbr / ft_strlen(base), base);
		if (isneg == -1)
			return (-1);
		counter += isneg;
	}
	if (write(1, &base[nbr % ft_strlen(base)], 1) == -1)
		return (-1);
	return (counter + 1);
}

int	ft_base(unsigned long current_value, char type)
{
	if (type == 'u')
		return (ft_putnbr_base(current_value, "0123456789"));
	else if (type == 'x')
		return (ft_putnbr_base(current_value, "0123456789abcdef"));
	else if (type == 'X')
		return (ft_putnbr_base(current_value, "0123456789ABCDEF"));
	return (-1);
}
