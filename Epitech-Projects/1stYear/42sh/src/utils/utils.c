/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Utility functions for string and array handling
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "error.h"
#include "shell.h"
#include "utils.h"

static int count_list(env_node_t *head)
{
    int count = 0;

    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

char **resize_array(char **old_array, int old_size, int new_size)
{
    char **new_array = malloc(new_size * sizeof(char *));

    if (!new_array) {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        exit(FAILURE);
    }
    for (int i = 0; i < old_size; i++)
        new_array[i] = old_array[i];
    free(old_array);
    return new_array;
}

char **parse_input(char *input)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token = NULL;

    if (!tokens)
        return NULL;
    token = strtok(input, " \t\n");
    while (token != NULL) {
        tokens[position] = strdup(token);
        position += 1;
        if (position >= bufsize) {
            bufsize += 64;
            tokens = resize_array(tokens, position, bufsize);
        }
        token = strtok(NULL, " \t\n");
    }
    tokens[position] = NULL;
    return tokens;
}

char **convert_env_list_to_array(env_node_t *env_list)
{
    env_node_t *current = env_list;
    int count = count_list(current);
    char **env_array = malloc(sizeof(char *) * (count + 1));
    int len = 0;

    if (!env_array)
        return NULL;
    current = env_list;
    for (int i = 0; i < count; i++) {
        len = strlen(current->key) + strlen(current->value) + 2;
        env_array[i] = malloc(len);
        if (!env_array[i])
            return NULL;
        strcpy(env_array[i], current->key);
        strcat(env_array[i], "=");
        strcat(env_array[i], current->value);
        current = current->next;
    }
    env_array[count] = NULL;
    return env_array;
}

void redirection_exit(char *file, int fd, int std)
{
    if (fd != -1) {
        if (dup2(fd, std) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    } else {
        perror(file);
        exit(1);
    }
}
