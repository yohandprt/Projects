/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** create_alias_list.c
*/

#include "alias.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void fill_alias_list(alias_t *alias, FILE *file)
{
    char *buffer = NULL;
    char **array = NULL;
    size_t size = 0;

    alias->attribute = NULL;
    alias->new_attribute = NULL;
    alias->next = NULL;
    while (getline(&buffer, &size, file) != -1) {
        array = my_str_to_word_array(buffer, "=\n");
        if (array == NULL || my_arraylen(array) != 2) {
            free(buffer);
            return;
        }
        add_alias(&alias, array[0], array[1]);
        free_array(array);
    }
    free(buffer);
}

alias_t *create_alias_list(void)
{
    alias_t *alias = malloc(sizeof(alias_t));
    int fd = open(".alias", O_RDONLY | O_CREAT, 0444);
    FILE *file = NULL;

    if (alias == NULL || fd == -1) {
        if (alias != NULL)
            free(alias);
        return NULL;
    }
    file = fdopen(fd, "r");
    if (file == NULL) {
        free(alias);
        close(fd);
        return NULL;
    }
    fill_alias_list(alias, file);
    close(fd);
    fclose(file);
    return alias;
}
