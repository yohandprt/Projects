/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** alias.h
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

    #include "shell.h"

typedef struct alias_s {
    char *attribute;
    char *new_attribute;
    struct alias_s *next;
} alias_t;

int builtin_alias(shell_state_t *shell, char **args);
int builtin_unalias(shell_state_t *shell, char **args);
int add_alias(alias_t **alias, char *attribute, char *new_attribute);
int remove_alias(alias_t **alias, char *attribute);
int file_alias(alias_t *alias);

alias_t *create_alias_list(void);

void free_alias(alias_t *alias);

#endif
