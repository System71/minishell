#ifndef MEMORY_MEM_H
# define MEMORY_MEM_H

# include <stddef.h>

typedef struct s_mem_node
{
    void               *ptr;
    struct s_mem_node  *next;
}   t_mem_node;
/**
 * Allocation sécurisée : quitte le programme en cas d'échec.
 * Enregistre chaque pointeur pour un libération ultérieure.
 */
void *ft_xmalloc(int size);

/**
 * Enregistre un pointeur alloué pour libération ultérieure.
 * Appelé automatiquement par xmalloc.
 */
void  mem_register(void *ptr);

/**
 * Libère tous les pointeurs enregistrés via mem_register.
 * Remet l'état du registre à zéro.
 */
void  mem_free_all(void);

#endif /* MEMORY_MEM_H */
