/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Help and usage information
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

void display_help(void)
{
    printf("USAGE\n");
    printf("    ./mysh\n\n");
    printf("DESCRIPTION\n");
    printf("\tmysh is a shell that can run commands, manage environment\n");
    printf("\tvariables, and handle pipes (|), semicolons (;), and\n");
    printf("\tredirections (>, <, >>, <<).\n");
}

int print_error(const char *message, int return_value)
{
    write(STDERR_FILENO, message, strlen(message));
    return return_value;
}
