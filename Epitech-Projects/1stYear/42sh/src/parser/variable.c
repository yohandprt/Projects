/*
** EPITECH PROJECT, 2024
** mainBranch
** File description:
** variable.c
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "parser.h"
#include "bash.h"
#include "environement.h"

static char *get_bash_variable(shell_state_t *shell, char *var_name)
{
    bash_var_t *bash_var = shell->bash_env->variables;

    while (bash_var) {
        if (strcmp(bash_var->name, var_name) == 0)
            return strdup(bash_var->value);
        bash_var = bash_var->next;
    }
    return NULL;
}

static char *get_variable_value(char *var_name, shell_state_t *shell)
{
    char *env_value = NULL;
    char exit_status[16];

    env_value = get_env_value(shell->env_list, var_name);
    if (env_value)
        return strdup(env_value);
    if (shell->bash_env) {
        env_value = get_bash_variable(shell, var_name);
        if (env_value)
            return env_value;
    }
    if (strcmp(var_name, "?") == 0) {
        sprintf(exit_status, "%d", shell->last_exit_status);
        return strdup(exit_status);
    }
    return NULL;
}

static void parse_braced_variable(int *var_len, int *idx[2], char *input,
    char *var_name)
{
    if (*var_len == 0 && input[*idx[0]] == '{') {
        *idx[0] += 1;
        *var_len = 0;
        while (input[*idx[0]] != '\0' && input[*idx[0]] != '}') {
            var_name[*var_len] = input[*idx[0]];
            *var_len += 1;
            *idx[0] += 1;
        }
        var_name[*var_len] = '\0';
        if (input[*idx[0]] == '}') {
            *idx[1] = *idx[0];
            *idx[0] += 1;
        }
    }
}

char *find_and_replace_var(char *input, int start_idx, int *end_idx,
    shell_state_t *shell)
{
    int i = start_idx + 1;
    char var_name[256] = {0};
    int var_len = 0;
    char *var_value = NULL;

    while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_')) {
        var_name[var_len] = input[i];
        var_len++;
        i++;
    }
    var_name[var_len] = '\0';
    *end_idx = i - 1;
    parse_braced_variable(&var_len, (int *[2]){&i, end_idx}, input, var_name);
    if (var_len == 0 && input[i] != '\0') {
        var_name[0] = input[i];
        var_name[1] = '\0';
        *end_idx = i;
    }
    var_value = get_variable_value(var_name, shell);
    return var_value ? var_value : strdup("");
}
