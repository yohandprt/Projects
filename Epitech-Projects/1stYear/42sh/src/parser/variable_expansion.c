/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Variable expansion and backtick substitution
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#include "shell.h"
#include "parser.h"
#include "environement.h"
#include "bash.h"
#include "error.h"

static void handle_single_quote(char *str, int *idx[2], char *result,
    bool *in_single_quotes)
{
    *in_single_quotes = !(*in_single_quotes);
    result[(*idx[1])] = str[(*idx[0])];
    (*idx[1])++;
    (*idx[0])++;
}

static void handle_variable_expansion(char *str, int *idx[2], char *result,
    shell_state_t *shell)
{
    int end_idx;
    char *var_value = find_and_replace_var(str, *idx[0], &end_idx, shell);

    if (var_value) {
        strcpy(result + *idx[1], var_value);
        *idx[1] += strlen(var_value);
        free(var_value);
        *idx[0] = end_idx + 1;
    } else {
        result[(*idx[1])] = str[(*idx[0])];
        (*idx[1])++;
        (*idx[0])++;
    }
}

static void copy_regular_character(char *str, int *i, char *result,
    int *result_len)
{
    result[(*result_len)] = str[(*i)];
    (*result_len)++;
    (*i)++;
}

static void setup_child_process(int pipefd[2], char *cmd, shell_state_t *shell)
{
    close(pipefd[0]);
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    close(pipefd[1]);
    execute_command_line(shell, cmd);
    exit(0);
}

static int read_from_pipe(int pipefd, char *buffer, int buffer_size)
{
    int total_read = 0;
    int bytes_read = read(pipefd, buffer + total_read,
        buffer_size - total_read - 1);

    while (bytes_read > 0) {
        total_read += bytes_read;
        bytes_read = read(pipefd, buffer + total_read,
            buffer_size - total_read - 1);
    }
    buffer[total_read] = '\0';
    return total_read;
}

static void trim_trailing_newline(char *buffer)
{
    int len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

static pid_t fork_process(int pipefd[2])
{
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
    }
    return pid;
}

char *expand_variables(char *str, shell_state_t *shell)
{
    char *result = malloc(4096);
    int result_len = 0;
    int i = 0;
    bool in_single_quotes = false;

    if (!str || !result)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] == '\'')
            handle_single_quote(str, (int *[2]){&i, &result_len}, result,
                &in_single_quotes);
        if (str[i] == '$' && !in_single_quotes)
            handle_variable_expansion(str, (int *[2]){&i, &result_len}, result,
                shell);
        else
            copy_regular_character(str, &i, result, &result_len);
    }
    result[result_len] = '\0';
    return result;
}

char *execute_backtick_command(char *cmd, shell_state_t *shell)
{
    int pipefd[2];
    pid_t pid;
    char buffer[4096] = {0};
    int status;

    pid = fork_process(pipefd);
    if (pid == -1)
        return strdup("");
    if (pid == 0) {
        setup_child_process(pipefd, cmd, shell);
    } else {
        close(pipefd[1]);
        read_from_pipe(pipefd[0], buffer, sizeof(buffer));
        waitpid(pid, &status, 0);
        close(pipefd[0]);
    }
    trim_trailing_newline(buffer);
    return strdup(buffer);
}
