/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** where.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "environement.h"
#include "utils.h"
#include "error.h"

static int builtins_and_relative(shell_state_t *shell, char *command)
{
    char *builtins[] = {"cd", "setenv", "unsetenv", "exit",
        "where", "which", NULL};

    for (int i = 0; builtins[i]; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            printf("%s is a shell built-in\n", command);
            return 1;
        }
    }
    if (strchr(command, '/')) {
        write(STDERR_FILENO, "where: / in command makes no sense\n", 35);
        shell->last_exit_status = 1;
        return 1;
    }
    return 0;
}

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

char **init_all_paths(shell_state_t *shell, const char *command)
{
    char **all_paths = NULL;
    char *path = get_env_value(shell->env_list, "PATH");
    char **paths = my_str_to_word_array(path, ":");
    char *full_path = NULL;
    int nb_paths = 0;

    if (!path || !paths || !command)
        return NULL;
    for (int i = 0; paths[i]; i++) {
        full_path = create_full_path(paths[i], command);
        if (!full_path)
            continue;
        if (access(full_path, X_OK) == 0)
            nb_paths++;
        free(full_path);
    }
    free_array(paths);
    all_paths = malloc(sizeof(char *) * (nb_paths + 1));
    return all_paths;
}

void add_new_path(char ***all_paths, char *full_path, int *index)
{
    (*all_paths)[*index] = strdup(full_path);
    (*index)++;
}

char **get_all_command_path(shell_state_t *shell, const char *command)
{
    char *path = get_env_value(shell->env_list, "PATH");
    char **paths = my_str_to_word_array(path, ":");
    char **all_paths = init_all_paths(shell, command);
    char *full_path = NULL;
    int index = 0;

    if (!path || !paths || !command)
        return NULL;
    for (int i = 0; paths[i]; i++) {
        full_path = create_full_path(paths[i], command);
        if (!full_path)
            continue;
        if (access(full_path, X_OK) == 0)
            add_new_path(&all_paths, full_path, &index);
        free(full_path);
    }
    all_paths[index] = NULL;
    free_array(paths);
    return all_paths;
}

int my_where(shell_state_t *shell, char **args)
{
    char **all_paths = NULL;

    shell->last_exit_status = 0;
    if (!(args[1]))
        return print_error("where: Too few arguments.\n", 1);
    for (int i = 1; args[i]; i++) {
        if (builtins_and_relative(shell, args[i]))
            continue;
        all_paths = get_all_command_path(shell, args[i]);
        if (!all_paths)
            continue;
        if (!(all_paths[0]))
            shell->last_exit_status = 1;
        for (int i = 0; all_paths[i]; i++)
            printf("%s\n", all_paths[i]);
        free_array(all_paths);
    }
    return shell->last_exit_status;
}
