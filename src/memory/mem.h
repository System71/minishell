/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:28:20 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/04 15:08:49 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

typedef struct s_mem_node
{
	void				*ptr;
	struct s_mem_node	*next;
}						t_mem_node;

void					*ft_xmalloc(int size);
void					mem_register(void *ptr);
void					mem_free_all(void);

#endif /* MEM_H */
