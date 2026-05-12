/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** backticks.c
*/

#include <string.h>
#include <stdlib.h>

#include "shell.h"
#include "parser.h"

static void init_backtick_state(backtick_state_t *state, char *input,
    shell_state_t *shell)
{
    state->input = input;
    state->result = malloc(4096);
    state->result_len = 0;
    state->pos = 0;
    state->in_backticks = false;
    state->backtick_start = 0;
    state->shell = shell;
}

static void append_cmd_output(backtick_state_t *state, char *cmd)
{
    int cmd_len = state->pos - state->backtick_start;
    char *cmd_output = NULL;

    strncpy(cmd, state->input + state->backtick_start, cmd_len);
    cmd[cmd_len] = '\0';
    cmd_output = execute_backtick_command(cmd, state->shell);
    if (cmd_output) {
        strcpy(state->result + state->result_len, cmd_output);
        state->result_len += strlen(cmd_output);
        free(cmd_output);
    }
}

static void process_current_char(backtick_state_t *state)
{
    char cmd[1024] = {0};

    if (state->input[state->pos] == '`') {
        if (!state->in_backticks) {
            state->backtick_start = state->pos + 1;
            state->in_backticks = true;
            state->pos++;
        } else {
            append_cmd_output(state, cmd);
            state->in_backticks = false;
            state->pos++;
        }
    } else if (!state->in_backticks) {
        state->result[state->result_len] = state->input[state->pos];
        state->result_len++;
        state->pos++;
    } else {
        state->pos++;
    }
}

char *process_backticks(char *input, shell_state_t *shell)
{
    backtick_state_t state;

    init_backtick_state(&state, input, shell);
    if (!state.result)
        return NULL;
    while (input[state.pos] != '\0')
        process_current_char(&state);
    state.result[state.result_len] = '\0';
    return state.result;
}
