/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_dynamic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:25:36 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/07 13:25:36 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Initialise le buffer dynamique
t_dynamic_buffer *init_dynamic_buffer(void)
{
    t_dynamic_buffer *buf = malloc(sizeof(t_dynamic_buffer));
    if (!buf)
        return NULL;
    buf->capacity = INITIAL_BUFFER_SIZE;
    buf->len = 0;
    buf->data = malloc(buf->capacity);
    if (!buf->data) {
        free(buf);
        return NULL;
    }
    buf->data[0] = '\0';
    return buf;
}

// Ajoute un caractère au buffer, en réallouant si nécessaire
int append_char(t_dynamic_buffer *buf, char c)
{
    // Si on approche de la capacité, on la double
    if (buf->len + 1 >= buf->capacity) {
        size_t new_capacity = buf->capacity * 2;
        char *new_data = realloc(buf->data, new_capacity);
        if (!new_data)
            return 0; // échec
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    buf->data[buf->len] = c;
    buf->len++;
    buf->data[buf->len] = '\0';
    return 1;
}

// Libère le buffer dynamique
void free_dynamic_buffer(t_dynamic_buffer *buf)
{
    if (buf) {
        free(buf->data);
        free(buf);
    }
}

// Exemple d'utilisation dans un lexer simplifié
char *lexer_example(const char *input)
{
    t_dynamic_buffer *buf = init_dynamic_buffer();
    if (!buf)
        return NULL;
    
    for (size_t i = 0; input[i] != '\0'; i++) {
        // Par exemple, on ajoute chaque caractère, mais ici tu peux insérer ta logique
        if (!append_char(buf, input[i])) {
            free_dynamic_buffer(buf);
            return NULL;
        }
    }
    // On retourne le contenu du buffer (il faudra le libérer plus tard)
    char *result = strdup(buf->data);
    free_dynamic_buffer(buf);
    return result;
}
