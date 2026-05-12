/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** which.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "environement.h"
#include "executor.h"
#include "utils.h"
#include "error.h"

static char *create_full_path(const char *directory, const char *command)
{
    char *full_path = malloc(strlen(directory) + strlen(command) + 2);

    if (!full_path)
        return NULL;
    strcpy(full_path, directory);
    strcat(full_path, "/");
    strcat(full_path, command);
    return full_path;
}

char *get_path_of_command(shell_state_t *shell, const char *command)
{
    char *path = get_env_value(shell->env_list, "PATH");
    char **paths = my_str_to_word_array(path, ":");
    char *full_path = NULL;

    if (!path || !paths)
        return NULL;
    for (int i = 0; paths[i]; i++) {
        full_path = create_full_path(paths[i], command);
        if (!full_path)
            continue;
        if (access(full_path, X_OK) == 0) {
            free_array(paths);
            return full_path;
        }
        free(full_path);
    }
    free_array(paths);
    return NULL;
}

void builtins_relative_and_not_found(shell_state_t *shell, char *command)
{
    char *builtins[] = {"cd", "setenv", "unsetenv", "exit",
        "where", "which", NULL};

    for (int i = 0; builtins[i]; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            printf("%s: shell built-in command.\n", command);
            return;
        }
    }
    write(STDERR_FILENO, command, strlen(command));
    write(STDERR_FILENO, ": Command not found.\n", 21);
    shell->last_exit_status = 1;
}

int my_which(shell_state_t *shell, char **args)
{
    char *path = NULL;

    shell->last_exit_status = 0;
    if (!args || !(args[1]))
        return print_error("which: Too few arguments.\n", 1);
    for (int i = 1; args[i]; i++) {
        path = get_path_of_command(shell, args[i]);
        if (path)
            printf("%s\n", path);
        else {
            builtins_relative_and_not_found(shell, args[i]);
            continue;
        }
        free(path);
    }
    return shell->last_exit_status;
}
