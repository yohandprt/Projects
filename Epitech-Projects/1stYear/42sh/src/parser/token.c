/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Enhanced token processing for quotes, backticks, and parentheses
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"
#include "executor.h"
#include "parser.h"
#include "shell.h"

static void add_command_to_list(command_list_t **head, command_t *cmd)
{
    command_list_t *new_node = malloc(sizeof(command_list_t));
    command_list_t *current = NULL;

    if (!new_node || !cmd)
        return;
    new_node->cmd = cmd;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

static command_t *finalize_command(command_list_t **cmd_list,
    command_t *current_cmd, token_type_t type)
{
    if (current_cmd->arg_count == 0)
        return current_cmd;
    current_cmd->args[current_cmd->arg_count] = NULL;
    if (type == PIPE)
        current_cmd->piped = true;
    add_command_to_list(cmd_list, current_cmd);
    return create_command();
}

static void handle_token_backticks(token_list_t *token, shell_state_t *shell,
    char *processed_token)
{
    char *backtick_result = process_backticks(token->token, shell);

    if (strchr(processed_token, '`')) {
        backtick_result = process_backticks(token->token, shell);
        if (backtick_result) {
            free(token->token);
            token->token = backtick_result;
        }
    }
}

static char *handle_token_quotes(char *processed_token)
{
    int len = strlen(processed_token);
    char *unquoted = malloc(len - 1);

    if (processed_token[0] == '\'' && processed_token[len - 1] == '\'' &&
            unquoted) {
        strncpy(unquoted, processed_token + 1, len - 2);
        unquoted[len - 2] = '\0';
        free(processed_token);
        processed_token = unquoted;
    } else if (processed_token[0] == '"' && processed_token[len - 1] == '"' &&
        unquoted) {
        strncpy(unquoted, processed_token + 1, len - 2);
        unquoted[len - 2] = '\0';
        free(processed_token);
        processed_token = unquoted;
    }
    return processed_token;
}

static void process_word_token(token_list_t *token, command_t *current,
    shell_state_t *shell)
{
    int len = 0;
    char *processed_token = strdup(token->token);
    char *expanded = NULL;

    if (!processed_token)
        return;
    len = strlen(processed_token);
    handle_token_backticks(token, shell, processed_token);
    if (strchr(processed_token, '$')) {
        expanded = expand_variables(processed_token, shell);
        if (expanded) {
            free(processed_token);
            processed_token = expanded;
        }
    }
    if (len >= 2)
        processed_token = handle_token_quotes(processed_token);
    current->args[current->arg_count] = processed_token;
    current->arg_count += 1;
}

static void handle_subshell(token_list_t *token, shell_state_t *shell)
{
    token_list_t *end_token = NULL;
    int result = execute_subshell(shell, token, &end_token);

    shell->last_exit_status = result;
    if (end_token)
        token = end_token;
}

static void handle_logical_operator(token_list_t **token,
    command_list_t **cmd_list, command_t **current, shell_state_t *shell)
{
    bool skip_next = false;

    *current = finalize_command(cmd_list, *current, (*token)->type);
    *current = (!*current) ? *current : create_command();
    if ((*token)->type == AND_OPERATOR)
        skip_next = (shell->last_exit_status != 0);
    else if ((*token)->type == OR_OPERATOR)
        skip_next = (shell->last_exit_status == 0);
    if (skip_next) {
        while (*token && (*token)->type != SEMICOLON)
            *token = (*token)->next;
        if (*token)
            *token = (*token)->prev;
    }
}

static void process_token(token_list_t **token, command_list_t **cmd_list,
    command_t **current, shell_state_t *shell)
{
    switch ((*token)->type) {
        case WORD:
            process_word_token(*token, *current, shell);
            break;
        case SEMICOLON:
        case PIPE:
            *current = finalize_command(cmd_list, *current, (*token)->type);
            *current = (!*current) ? *current : create_command();
            break;
        case AND_OPERATOR:
        case OR_OPERATOR:
            handle_logical_operator(token, cmd_list, current, shell);
            break;
        default:
            *token = process_redirect(*token, *current);
            break;
    }
}

static void finalize_command_list(command_list_t **cmd_list,
    command_t *current_cmd)
{
    if (current_cmd->arg_count > 0) {
        current_cmd->args[current_cmd->arg_count] = NULL;
        add_command_to_list(cmd_list, current_cmd);
    } else {
        free_command(current_cmd);
    }
}

command_list_t *build_command_list(token_list_t *tokens, shell_state_t *shell)
{
    command_list_t *cmd_list = NULL;
    command_t *current_cmd = create_command();
    token_list_t *token = tokens;

    if (!current_cmd)
        return NULL;
    while (token != NULL) {
        if (token->type == PAREN_OPEN)
            handle_subshell(token, shell);
        else
            process_token(&token, &cmd_list, &current_cmd, shell);
        if (!current_cmd)
            free_command_list(cmd_list);
        if (!token || !current_cmd)
            return NULL;
        token = token->next;
    }
    finalize_command_list(&cmd_list, current_cmd);
    return cmd_list;
}
