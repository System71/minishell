/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:29:44 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:57:03 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tamp;

	while (*lst)
	{
		(*del)((*lst)->content);
		tamp = *lst;
		*lst = (*lst)->next;
		free(tamp);
	}
	lst = NULL;
}
