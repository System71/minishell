/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:59:37 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 14:59:55 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespace(int c)
{
    if (c == ' ')
        return (1);
    if (c == '\t')
        return (1);
    if (c == '\n')
        return (1);
    if (c == '\v')
        return (1);
    if (c == '\f')
        return (1);
    if (c == '\r')
        return (1);
    return (0);
}
