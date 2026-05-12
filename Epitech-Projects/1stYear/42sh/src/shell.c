/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Main shell loop and input handling
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "error.h"
#include "shell.h"
#include "utils.h"
#include "builtins.h"
#include "bash.h"
#include "executor.h"
#include "environement.h"

static char *find_path(void)
{
    char *home = getenv("HOME");

    if (!home)
        return NULL;
    strcat(home, "/.42sh_history");
    return home;
}

void display_prompt(env_node_t *env_list)
{
    char *user = get_env_value(env_list, "USER");
    char *cwd = getcwd(NULL, 0);

    if (!user)
        user = "null";
    if (!cwd)
        cwd = "/";
    printf("%s%s@42sh%s:%s%s%s:$> ",
        TURQUOISE, user, RESET, GREEN, cwd, BLUE);
    free(cwd);
}

int handle_builtin(shell_state_t *shell, char *input)
{
    int index = 0;
    char **args = parse_input(input);

    if (args[0] == NULL) {
        free_array(args);
        return SUCCESS;
    }
    while (builtin_handler[index].name != NULL) {
        if (strcmp(args[0], builtin_handler[index].name) == 0) {
            shell->last_exit_status = builtin_handler[index].func(shell, args);
            free_array(args);
            return SUCCESS;
        }
        index++;
    }
    shell->last_exit_status = execute_single_command(shell, args);
    free_array(args);
    return SUCCESS;
}

int handle_input(shell_state_t *shell, char *input)
{
    int result = 0;

    if (!input || input[0] == '\0')
        return SUCCESS;
    if (input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';
    if (strcmp(input, "exit") == 0) {
        if (isatty(STDIN_FILENO))
            printf("exit\n");
        return FAILURE;
    }
    result = execute_command_line(shell, input);
    return result;
}

void start_minishell(shell_state_t *shell)
{
    char *input = NULL;
    char *path_history = find_path();
    size_t len = 0;
    int result = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            display_prompt(shell->env_list);
        if (getline(&input, &len, stdin) == -1) {
            printf("\n");
            break;
        }
        if (path_history)
            adding_in_history(input, path_history);
        result = handle_input(shell, input);
        if (result == FAILURE)
            break;
    }
    free(input);
}
