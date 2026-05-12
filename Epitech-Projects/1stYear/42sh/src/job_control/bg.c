/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** bg.c
*/

#include "job_control.h"
#include "shell.h"
#include "executor.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void add_job(jobs_t **jobs, char *cmd, int pid)
{
    jobs_t *new_job = malloc(sizeof(jobs_t));
    jobs_t *current;
    int i = 1;

    new_job->cmd = strdup(cmd);
    new_job->pid = pid;
    new_job->index = 1;
    new_job->next = NULL;
    if (!(*jobs))
        *jobs = new_job;
    else {
        current = *jobs;
        while (current->next != NULL) {
            i++;
            current = current->next;
        }
        new_job->index = i;
        current->next = new_job;
    }
    printf("[%d] %d\n", i, pid);
}

void handle_background(jobs_t **jobs, char *cmd, int pid, int background)
{
    if (background)
        add_job(jobs, cmd, pid);
    else {
        waitpid(pid, NULL, 0);
        printf("[%d]  + %d done       %s\n", 0, pid, cmd);
    }
}

int execute_bg_command(jobs_t **jobs, char *cmd, char **args, char **envp)
{
    int pid = 0;
    int background = 1; // j'enleverrais quand le code sera connecté à mysh
    // char *cmd_path = get_command_path(shell, args);

    pid = fork();
    if (pid == 0)
        execve("/bin/ls", args, envp);
    else if (pid > 0)
        handle_background(jobs, cmd, pid, background);
    else
        perror("fork");
}

int main(int argc, char **argv, char **envp)
{
    jobs_t *jobs = NULL;
    char *args[] = {"ls", "-l", NULL};

    printf("add :\n");
    execute_bg_command(&jobs, "ls", args, envp);
    printf("\njobs :\n");
    display_jobs(&jobs, 0);
    printf("\njobs -l :\n");
    display_jobs(&jobs, 1);
}
