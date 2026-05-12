/*
** EPITECH PROJECT, 2025
** amazed.c
** File description:
** amazed.c
*/

#include "amazed.h"

int main(void)
{
    graph_t *graph = init_graph();

    if (!graph)
        return 84;
    find_all_path(graph);
    sort_path(graph);
    output(graph);
    process_paths_directly(graph);
    free_graph(graph);
    return 0;
}
