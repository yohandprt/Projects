/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** init_shell.c
*/

#include "bash.h"
#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

shell_state_t *init_shell(const char **envp)
{
    shell_state_t *shell = malloc(sizeof(shell_state_t));

    if (shell == NULL)
        return NULL;
    shell->env_list = NULL;
    shell->last_exit_status = 0;
    shell->bash_env = create_bash_env();
    if (shell->bash_env == NULL) {
        free(shell);
        return NULL;
    }
    load_bash_env(shell->bash_env, envp);
    return shell;
}

void cleanup_shell(shell_state_t *shell)
{
    env_node_t *current = shell->env_list;
    env_node_t *next;

    if (shell->bash_env)
        destroy_bash_env(shell->bash_env);
    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(shell);
}
