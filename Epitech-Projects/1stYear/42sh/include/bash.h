/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** bash.h
*/

#ifndef BASH_H_
    #define BASH_H_

    #include "shell.h"

typedef struct bash_var_s {
    char *name;
    char *value;
    struct bash_var_s *next;
} bash_var_t;

typedef struct bash_env_s {
    bash_var_t *variables;
    int size;
} bash_env_t;

// Creation and destruction functions (init_shell.c)
bash_env_t *create_bash_env(void);
void destroy_bash_env(bash_env_t *env);
bash_var_t *create_bash_var(const char *name, const char *value);
int load_bash_env(bash_env_t *env, const char **envp);

// Environment manipulation functions (set.c)
int parse_bash_var_line(char *line, bash_env_t *env);
int set_bash_var(bash_env_t *env, const char *name, const char *value);
int unset_bash_var(bash_env_t *env, const char *name);
void display_bash_env(bash_env_t *env);
int env_bash(const char **envp);

void handle_variable_query(shell_state_t *shell, const char *query);

#endif
