/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:39:19 by prigaudi          #+#    #+#             */
/*   Updated: 2024/12/02 09:09:40 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base_ptr(unsigned long nbr, char *base)
{
	int	counter;
	int	isneg;

	isneg = 0;
	counter = 0;
	if (nbr >= ft_strlen(base))
	{
		isneg = ft_putnbr_base_ptr(nbr / ft_strlen(base), base);
		if (isneg == -1)
			return (-1);
		counter += isneg;
	}
	if (write(1, &base[nbr % ft_strlen(base)], 1) == -1)
		return (-1);
	return (counter + 1);
}

int	ft_pointer(unsigned long current_value)
{
	int	counter;
	int	isneg;

	counter = 0;
	if (current_value == 0)
		return (ft_string("(nil)"));
	isneg = ft_string("0x");
	if (isneg == -1)
		return (-1);
	counter += isneg;
	isneg = ft_putnbr_base_ptr(current_value, "0123456789abcdef");
	if (isneg == -1)
		return (-1);
	counter += isneg;
	return (counter);
}
