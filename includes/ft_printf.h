/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:32 by prigaudi          #+#    #+#             */
/*   Updated: 2024/12/02 09:07:15 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_character(int current_value);
int		ft_string(char *current_value);
int		ft_pointer(unsigned long current_value);
int		ft_decimal(int current_value);
int		ft_base(unsigned long current_value, char type);
size_t	ft_strlen(const char *str);

#endif