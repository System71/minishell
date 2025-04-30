/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:42:21 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/29 13:07:15 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

static t_mem_node *g_mem_list = NULL;

void	*ft_xmalloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("minishell: malloc");
		mem_free_all();
		exit(EXIT_FAILURE);
	}
	mem_register(ptr);
	return (ptr);
}

void  mem_register(void *ptr)
{
    t_mem_node  *node;

    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        perror("minishell: malloc");
        exit(EXIT_FAILURE);
    }
    node->ptr  = ptr;
    node->next = g_mem_list;
    g_mem_list = node;
}

void  mem_free_all(void)
{
    t_mem_node  *current;
    t_mem_node  *tmp;

    current = g_mem_list;
    while (current != NULL)
    {
        free(current->ptr);
        tmp = current;
        current = current->next;
        free(tmp);
    }
    g_mem_list = NULL;
}
