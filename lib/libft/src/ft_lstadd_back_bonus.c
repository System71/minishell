/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:44:16 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 14:31:30 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tamp;

	tamp = *lst;
	if (tamp == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	while (tamp->next != NULL)
		tamp = tamp->next;
	tamp->next = new;
}
