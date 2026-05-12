/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Command execution logic with enhanced parser
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "bash.h"
#include "error.h"
#include "shell.h"
#include "utils.h"
#include "builtins.h"
#include "executor.h"
#include "redirection.h"
#include "parser.h"

static char *preprocess_command(char *input, shell_state_t *shell)
{
    char *expanded = NULL;
    char *processed = NULL;

    processed = process_backticks(input, shell);
    if (!processed)
        return strdup(input);
    expanded = expand_variables(processed, shell);
    free(processed);
    return expanded ? expanded : strdup(input);
}

static command_list_t *move_to_next_command_set(command_list_t *current)
{
    while (current && current->cmd->piped)
        current = current->next;
    if (current)
        current = current->next;
    return current;
}

int check_and_execute_builtin(shell_state_t *shell, command_t *cmd)
{
    for (int i = 0; builtin_handler[i].name != NULL; i++) {
        if (strcmp(cmd->args[0], builtin_handler[i].name) == 0) {
            return builtin_handler[i].func(shell, cmd->args);
        }
    }
    return -1;
}

int execute_simple_command(shell_state_t *shell, command_t *cmd)
{
    int result = 0;
    int stdin_copy = -1;
    int stdout_copy = -1;

    if (!cmd || !cmd->args || !cmd->args[0])
        return 0;
    if (setup_redirections(cmd, &stdin_copy, &stdout_copy) == -1)
        return 1;
    if (handle_bash_command(shell, cmd->args) == 0) {
        reset_redirections(stdin_copy, stdout_copy);
        return shell->last_exit_status;
    }
    result = check_and_execute_builtin(shell, cmd);
    if (result != -1) {
        reset_redirections(stdin_copy, stdout_copy);
        return result;
    }
    result = execute_single_command(shell, cmd->args);
    reset_redirections(stdin_copy, stdout_copy);
    return result;
}

int execute_commands(shell_state_t *shell, command_list_t *cmd_list)
{
    int result = 0;
    command_list_t *current = cmd_list;

    while (current != NULL) {
        if (current->cmd->piped) {
            result = execute_piped_commands(shell, current);
            current = move_to_next_command_set(current);
        } else {
            result = execute_simple_command(shell, current->cmd);
            current = current->next;
        }
        shell->last_exit_status = result;
    }
    return result;
}

static int handle_bash_var(shell_state_t *shell, char *processed_input)
{
    if (processed_input[0] == '?') {
        handle_variable_query(shell, processed_input);
        free(processed_input);
        return SUCCESS;
    }
    return -1;
}

static int process_and_execute(shell_state_t *shell, char *processed_input)
{
    token_list_t *tokens = parse_command_line(processed_input);
    command_list_t *commands = NULL;

    if (!tokens) {
        free(processed_input);
        shell->last_exit_status = 1;
        return SUCCESS;
    }
    commands = build_command_list(tokens, shell);
    free_token_list(tokens);
    if (!commands) {
        shell->last_exit_status = 1;
        free(processed_input);
        return SUCCESS;
    }
    shell->last_exit_status = execute_commands(shell, commands);
    free_command_list(commands);
    free(processed_input);
    return SUCCESS;
}

int execute_command_line(shell_state_t *shell, char *input)
{
    char *processed_input = preprocess_command(input, shell);

    if (handle_bash_var(shell, processed_input) == SUCCESS)
        return SUCCESS;
    return process_and_execute(shell, processed_input);
}
