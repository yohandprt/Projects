/*
** EPITECH PROJECT, 2025
** read_file
** File description:
** read the file and return a string
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char *read_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    struct stat sb;
    char *content = NULL;

    if (fd == -1)
        return NULL;
    stat(file_name, &sb);
    content = malloc(sizeof(char) * (sb.st_size + 1));
    read(fd, content, sb.st_size);
    content[sb.st_size] = '\0';
    close(fd);
    return content;
}
