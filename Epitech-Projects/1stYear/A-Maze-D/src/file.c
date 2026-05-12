/*
** EPITECH PROJECT, 2025
** file.c
** File description:
** file
*/

#include "amazed.h"

char **read_file(void)
{
    char **lines = malloc(sizeof(char *) * 1);
    int ind = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        lines = my_realloc(lines, sizeof(char *) * ind,
        sizeof(char *) * (ind + 2));
        lines[ind] = my_strdup(line);
        if (lines[ind][my_strlen(line) - 1] == '\n')
            lines[ind][my_strlen(line) - 1] = '\0';
        ind++;
    }
    if (ind == 0)
        return NULL;
    lines[ind] = NULL;
    free(line);
    return lines;
}
