/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** alias.c
*/

#include "alias.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

void init_alias(alias_t *alias)
{
    alias->attribute = NULL;
    alias->new_attribute = NULL;
    alias->next = NULL;
}

void free_alias(alias_t *alias)
{
    alias_t *tmp;

    while (alias != NULL) {
        tmp = alias;
        alias = alias->next;
        free(tmp->attribute);
        free(tmp->new_attribute);
        free(tmp);
    }
}

int add_alias(alias_t **alias, char *attribute, char *new_attribute)
{
    alias_t *new_alias = malloc(sizeof(alias_t));
    alias_t *current = *alias;

    if (new_alias == NULL)
        return 84;
    init_alias(new_alias);
    new_alias->attribute = strdup(attribute);
    new_alias->new_attribute = strdup(new_attribute);
    if (new_alias->attribute == NULL || new_alias->new_attribute == NULL) {
        free(new_alias);
        return 84;
    }
    if (*alias == NULL) {
        *alias = new_alias;
        return 0;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_alias;
    return 0;
}

static int remove_alias_node(alias_t **alias, alias_t *current,
    alias_t *prev)
{
    if (prev == NULL)
        *alias = current->next;
    else
        prev->next = current->next;
    free(current->attribute);
    free(current->new_attribute);
    free(current);
    return 0;
}

int remove_alias(alias_t **alias, char *attribute)
{
    alias_t *current = *alias;
    alias_t *prev = NULL;

    while (current != NULL) {
        if (current->attribute && current->new_attribute &&
            strcmp(current->attribute, attribute) == 0) {
            remove_alias_node(alias, current, prev);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return 84;
}

int file_alias(alias_t *alias)
{
    int fd = open(".alias", O_WRONLY | O_CREAT, 0444);
    char *str = NULL;

    if (fd == -1 || alias == NULL)
        return 84;
    while (alias != NULL) {
        str = malloc(sizeof(char) * (strlen(alias->attribute) +
        strlen(alias->new_attribute) + 2));
        if (str == NULL)
            return 84;
        sprintf(str, "%s=%s\n", alias->attribute, alias->new_attribute);
        write(fd, str, strlen(str));
        free(str);
        alias = alias->next;
    }
    close(fd);
    return 0;
}
