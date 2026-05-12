/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** job_control.h
*/

#ifndef _JOB_CONTROL_H_
    #define _JOB_CONTROL_H_

typedef struct jobs_s {
    int index;
    char *cmd;
    int pid;
    struct jobs_s *next;
} jobs_t;

int execute_bg_command(jobs_t **jobs, char *cmd, char **args, char **envp);
void display_jobs(jobs_t **jobs, int l_opt);

#endif
