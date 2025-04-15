/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_temp_filename.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:42:34 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/15 11:42:34 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define TMP_DIR "/tmp"
#define PREFIX "heredoc_"
#define MAX_TRY 10000

char    *generate_temp_filename(void)
{
    char    *filename;
    int     counter;
    int     fd;

    filename = malloc(256);
    if (!filename)
        return NULL;
    counter = 0;
    while (counter < MAX_TRY)
    {
        /* Construit le chemin du fichier temporaire */
        snprintf(filename, 256, "%s/%s%d", TMP_DIR, PREFIX, counter);
        /* Tente de créer le fichier de manière atomique */
        fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
        if (fd != -1)
        {
            /* Le fichier a été créé avec succès.
               On ferme le descripteur et on retourne le nom */
            close(fd);
            return filename;
        }
        counter++;
    }
    free(filename);
    return NULL;
}
