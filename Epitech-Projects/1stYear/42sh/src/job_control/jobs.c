/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** jobs.c
*/

#include "job_control.h"
#include <stdio.h>

void display_jobs(jobs_t **jobs, int l_opt)
{
    jobs_t *current;

    if (!(*jobs))
        return;
    current = *jobs;
    while (current) {
        if (l_opt)
            printf("[%d]  + %d running    %s\n", current->index,
                current->pid, current->cmd);
        else
            printf("[%d]  + running    %s\n", current->index, current->cmd);
        current = current->next;
    }
}
