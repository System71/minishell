/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:28:20 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 07:07:41 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

typedef struct s_mem_node
{
	void				*ptr;
	struct s_mem_node	*next;
}		t_mem_node;

void	*ft_xmalloc(int size, int which_list);
void	mem_register(void *ptr, int which_list);
void	mem_free_all(int which_list);
void	ft_free_loop(char *input);

#endif /* MEM_H */
