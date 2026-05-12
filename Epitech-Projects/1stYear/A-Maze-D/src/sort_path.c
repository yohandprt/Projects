/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-thomas.villot
** File description:
** sort_path.c
*/

#include "amazed.h"

void my_swap_array(int **a, int **b)
{
    int *temp = *a;

    *a = *b;
    *b = temp;
}

void reverse(graph_t *graph, int i, int j)
{
    if (graph->path->length_path[i] < graph->path->length_path[j]) {
        my_swap_array(&graph->path->all_path[i], &graph->path->all_path[j]);
        my_swap(&graph->path->length_path[i], &graph->path->length_path[j]);
        return;
    }
    if (graph->path->length_path[i] == graph->path->length_path[j]) {
        if (graph->path->all_path[i][1] < graph->path->all_path[j][1]) {
            my_swap_array(&graph->path->all_path[i],
                &graph->path->all_path[j]);
            my_swap(&graph->path->length_path[i],
                &graph->path->length_path[j]);
        }
    }
}

void sort_path(graph_t *graph)
{
    if (!graph || !graph->path || !graph->path->all_path ||
        graph->path->nb_path <= 0)
        return;
    for (int i = 0; i < graph->path->nb_path; i++) {
        for (int j = 0; j < graph->path->nb_path; j++) {
            reverse(graph, i, j);
        }
    }
}
