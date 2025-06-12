/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:22:10 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:22:10 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int wich_list)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (ft_xmalloc(new_size, wich_list));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_xmalloc(new_size, wich_list);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	return (new_ptr);
}
