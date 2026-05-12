/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** 42sh.h
*/

#ifndef SHELL_H_
    #define SHELL_H_

/* Environment variable linked list */
typedef struct env_node_s {
    char *key;
    char *value;
    struct env_node_s *next;
} env_node_t;

/* Forward declaration */
typedef struct bash_env_s bash_env_t;
typedef struct command_list_s command_list_t;
typedef struct alias_s alias_t;

/* Shell state */
typedef struct shell_state_s {
    env_node_t *env_list;
    int last_exit_status;
    bash_env_t *bash_env;
    alias_t *alias_list;
} shell_state_t;

/* Main shell functions */
void start_minishell(shell_state_t *shell);
int handle_input(shell_state_t *shell, char *input);
int handle_builtin(shell_state_t *shell, char *input);
void display_prompt(env_node_t *env_list);

/* Builtin handlers table */
typedef struct builtin_s {
    char *name;
    int (*func)(shell_state_t *, char **);
} builtin_t;

/* Variable expansion and command substitution */
char *expand_variables(char *str, shell_state_t *shell);
char *execute_backtick_command(char *cmd, shell_state_t *shell);
char *process_backticks(char *input, shell_state_t *shell);

/* History */
int adding_in_history(char *input, char *path_history);
int handle_bash_command(shell_state_t *shell, char **args);

char **expand_globbing(char **args);

#endif
