/*
** EPITECH PROJECT, 2025
** history
** File description:
** handle the history of the cmd
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

int adding_in_history(char *input, char *path_history)
{
    int fd = -1;

    fd = open(path_history, O_APPEND | O_WRONLY | O_CREAT, 0600);
    if (fd == -1)
        return 84;
    write(fd, input, strlen(input));
    close(fd);
    return 0;
}

char **recover_history(char *path_history)
{
    char *history_file = read_file(path_history);
    char **history = NULL;

    if (!history_file)
        return NULL;
    history = my_str_to_word_array(history_file, "\n");
    return history;
}
