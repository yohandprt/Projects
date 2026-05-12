/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Subshell execution for parentheses support
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "error.h"
#include "shell.h"
#include "bash.h"
#include "parser.h"
#include "executor.h"
#include "environement.h"

static void add_to_buffer(char *buffer, int *len, const char *token,
    int buffer_size)
{
    int token_len = strlen(token);

    if (*len > 0 && *len < buffer_size - 1) {
        buffer[*len] = ' ';
        (*len)++;
    }
    if (*len + token_len < buffer_size - 1) {
        strcat(buffer + *len, token);
        *len += token_len;
    }
}

static int extract_subshell_command(token_list_t *start, token_list_t **end,
    char *buffer, int buffer_size)
{
    token_list_t *current = start->next;
    int paren_count = 1;
    int len = 0;

    buffer[0] = '\0';
    while (current && paren_count > 0) {
        if (current->type == PAREN_OPEN)
            paren_count++;
        if (current->type == PAREN_CLOSE)
            paren_count--;
        if (!(current->type == PAREN_CLOSE && paren_count == 0))
            add_to_buffer(buffer, &len, current->token, buffer_size);
        if (paren_count == 0)
            *end = current;
        current = current->next;
    }
    return (paren_count == 0) ? 0 : -1;
}

static void subshell_child_process(shell_state_t *shell, char *cmd_buffer,
    int pipefd[2])
{
    shell_state_t subshell;

    close(pipefd[0]);
    init_shell_state(&subshell, shell);
    execute_command_line(&subshell, cmd_buffer);
    write(pipefd[1], &subshell.last_exit_status, sizeof(int));
    close(pipefd[1]);
    free_shell_state(&subshell);
    exit(0);
}

static int subshell_parent_process(int pipefd[2], int pid)
{
    int exit_status = 0;
    int status = 0;

    close(pipefd[1]);
    waitpid(pid, &status, 0);
    read(pipefd[0], &exit_status, sizeof(int));
    close(pipefd[0]);
    return exit_status;
}

static int create_subshell_pipe(pid_t *pid, int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    *pid = fork();
    if (*pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }
    return 0;
}

int execute_subshell(shell_state_t *shell, token_list_t *start_token,
    token_list_t **end_token)
{
    char cmd_buffer[4096] = {0};
    int pipefd[2];
    pid_t pid;

    if (extract_subshell_command(start_token, end_token, cmd_buffer,
        sizeof(cmd_buffer)) != 0) {
        print_error("Malformed subshell command\n", 1);
        return 1;
    }
    if (create_subshell_pipe(&pid, pipefd) == 1)
        return 1;
    if (pid == 0)
        subshell_child_process(shell, cmd_buffer, pipefd);
    return subshell_parent_process(pipefd, pid);
}

void init_shell_state(shell_state_t *dest, shell_state_t *src)
{
    bash_var_t *var = NULL;
    env_node_t *current = NULL;

    dest->last_exit_status = src->last_exit_status;
    dest->env_list = NULL;
    current = src->env_list;
    while (current != NULL) {
        dest->env_list = add_env_node(dest->env_list, current->key,
            current->value);
        current = current->next;
    }
    dest->bash_env = create_bash_env();
    if (src->bash_env && src->bash_env->variables) {
        var = src->bash_env->variables;
        while (var != NULL) {
            set_bash_var(dest->bash_env, var->name, var->value);
            var = var->next;
        }
    }
}
