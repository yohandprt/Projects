/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** bash_env.c
*/

#include "bash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bash_env_t *create_bash_env(void)
{
    bash_env_t *env = malloc(sizeof(bash_env_t));

    if (env == NULL)
        return NULL;
    env->variables = NULL;
    env->size = 0;
    return env;
}

void destroy_bash_env(bash_env_t *env)
{
    bash_var_t *current = env->variables;
    bash_var_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    free(env);
}

bash_var_t *create_bash_var(const char *name, const char *value)
{
    bash_var_t *var = malloc(sizeof(bash_var_t));

    if (var == NULL)
        return NULL;
    var->name = strdup(name);
    var->value = strdup(value);
    if (var->name == NULL || var->value == NULL) {
        free(var->name);
        free(var->value);
        free(var);
        return NULL;
    }
    var->next = NULL;
    return var;
}

static int set_env_var(bash_env_t *env, char *key, char *value, char *env_var)
{
    int result = 0;

    if (key && value) {
        result = set_bash_var(env, key, value);
        if (result != 0) {
            free(env_var);
            return result;
        }
    }
    return 0;
}

int load_bash_env(bash_env_t *env, const char **envp)
{
    char *key = NULL;
    char *value = NULL;
    char *env_var = NULL;
    int result = 0;

    if (!env || !envp)
        return 84;
    for (int i = 0; envp[i] != NULL; i++) {
        env_var = strdup(envp[i]);
        if (!env_var)
            return 84;
        key = strtok(env_var, "=");
        value = strtok(NULL, "");
        result = set_env_var(env, key, value, env_var);
        if (result != 0)
            return result;
        free(env_var);
    }
    return 0;
}
