/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:49:20 by prigaudi          #+#    #+#             */
/*   Updated: 2024/12/02 11:36:29 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	launcher(va_list params, char type)
{
	if (type == 'c')
		return (ft_character(va_arg(params, int)));
	else if (type == 'd' || type == 'i')
		return (ft_decimal(va_arg(params, int)));
	else if (type == 'u' || type == 'x' || type == 'X')
		return (ft_base(va_arg(params, unsigned long), type));
	else if (type == 'p')
		return (ft_pointer(va_arg(params, unsigned long)));
	else if (type == 's')
		return (ft_string(va_arg(params, char *)));
	else if (type == '%')
	{
		return (write(1, &type, 1));
	}
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	char	type;
	int		counter;
	va_list	params;

	va_start(params, str);
	counter = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			type = *str;
			counter += launcher(params, type);
		}
		else
		{
			if (write(1, str, 1) == -1)
				return (-1);
			counter++;
		}
		str++;
	}
	va_end(params);
	return (counter);
}
