/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** set.c
*/

#include "bash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bash_var_t *find_name(bash_env_t *env, const char *name)
{
    bash_var_t *current = env->variables;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

static int remove_variable(bash_env_t *env, bash_var_t *current,
    bash_var_t *prev)
{
    if (prev == NULL)
        env->variables = current->next;
    else
        prev->next = current->next;
    free(current->name);
    free(current->value);
    free(current);
    env->size--;
    return 0;
}

const char *get_bash_var_value(bash_env_t *env, const char *name)
{
    bash_var_t *var;

    var = find_name(env, name);
    if (var != NULL)
        return var->value;
    return NULL;
}

void handle_variable_query(shell_state_t *shell, const char *query)
{
    const char *var_name;
    const char *value;

    if (query[0] == '?') {
        var_name = query + 1;
        value = get_bash_var_value(shell->bash_env, var_name);
        if (value != NULL)
            printf("%s\n", value);
        else
            printf("Variable '%s' not found\n", var_name);
    }
}

int set_bash_var(bash_env_t *env, const char *name, const char *value)
{
    bash_var_t *var;

    var = find_name(env, name);
    if (var != NULL) {
        free(var->value);
        var->value = strdup(value);
        return (var->value == NULL) ? 84 : 0;
    }
    var = create_bash_var(name, value);
    if (var == NULL)
        return 84;
    var->next = env->variables;
    env->variables = var;
    env->size++;
    return 0;
}

int unset_bash_var(bash_env_t *env, const char *name)
{
    bash_var_t *current = env->variables;
    bash_var_t *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return remove_variable(env, current, prev);
        prev = current;
        current = current->next;
    }
    return 1;
}

void display_bash_env(bash_env_t *env)
{
    bash_var_t *current = env->variables;

    while (current != NULL) {
        printf("%s\t%s\n", current->name, current->value);
        current = current->next;
    }
}
