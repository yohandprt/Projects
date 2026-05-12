/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** executor.h
*/

#include <sys/types.h>
#include <stdbool.h>

#include "shell.h"

#ifndef EXECUTOR_H_
    #define EXECUTOR_H_

/* Structure to represent a single command */
typedef struct command_s {
    char **args;
    int arg_count;
    char *in_file;    /* For input redirection (<) */
    char *out_file;   /* For output redirection (>) */
    bool append;      /* For >> redirection */
    bool heredoc;     /* For << redirection */
    bool piped;       /* If command pipes to next command */
} command_t;

/* Linked list of commands */
typedef struct command_list_s {
    command_t *cmd;
    struct command_list_s *next;
} command_list_t;

/* Command execution */
int execute_single_command(shell_state_t *shell, char **args);
char *get_command_path(shell_state_t *shell, char **args);
int handle_exit_status(int status);
int execute_command_line(shell_state_t *shell, char *input);
int execute_commands(shell_state_t *shell, command_list_t *cmd_list);
int execute_simple_command(shell_state_t *shell, command_t *cmd);
void handle_parent_pipes(int *prev_pipe, int *pipefd, bool is_last);
void create_pipe_and_fork(int *pipefd, pid_t *pid, bool is_last);
int wait_for_pipe_children(pid_t *pids, int cmd_count);
int execute_piped_commands(shell_state_t *shell, command_list_t *cmd_list);
int check_and_execute_builtin(shell_state_t *shell, command_t *cmd);
void execute_child_process(char *cmd_path, char **args, shell_state_t *shell);

#endif
