/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:21:59 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:59:46 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new_list;
	void	*new_content;

	result = NULL;
	if (lst == NULL || f == NULL)
		return (result);
	while (lst)
	{
		new_content = f(lst->content);
		new_list = ft_lstnew(new_content);
		if (new_list == NULL)
		{
			del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_list);
		lst = lst->next;
	}
	return (result);
}
