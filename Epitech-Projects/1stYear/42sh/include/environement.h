/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** environement.h
*/

#include "shell.h"

#ifndef ENVIRONMENT_H_
    #define ENVIRONMENT_H_

/* Environment management */
env_node_t *init_env_list(char const **envp);
env_node_t *add_env_node(env_node_t *head, const char *key, const char *value);
void free_env_list(env_node_t *head);
char *get_env_value(env_node_t *env_list, const char *key);
env_node_t *create_reversed_copy(env_node_t *head);
char **convert_env_list_to_array(env_node_t *env_list);

#endif
