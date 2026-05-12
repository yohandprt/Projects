/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** redirection.h
*/

#include "executor.h"

#ifndef REDIRECTION_H_
    #define REDIRECTION_H_

int setup_redirections(command_t *cmd, int *stdin_copy, int *stdout_copy);
int reset_redirections(int stdin_copy, int stdout_copy);
int handle_heredoc(char *delimiter);
void redirection_exit(char *file, int fd, int std);

#endif
