/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-thomas.villot
** File description:
** moves.c
*/

#include "amazed.h"
#include <limits.h>

int all_robots_finished(graph_t *graph, int step)
{
    for (int robot = 0; robot < graph->path->nb_path; robot++) {
        if (step < graph->path->length_path[robot] - 1)
            return 0;
    }
    return 1;
}

int find_shortest_path(graph_t *graph)
{
    int min_length = INT_MAX;

    for (int i = 0; i < graph->path->nb_path; i++) {
        if (graph->path->length_path[i] < min_length &&
            graph->path->length_path[i] > 0)
            min_length = graph->path->length_path[i];
    }
    return min_length;
}

void fill_path_room(graph_t *graph, int path_length, char **array)
{
    for (int j = 0; j < path_length; j++)
        array[j] = my_int_to_str(graph->path->all_path[0][j]);
}

void process_paths_directly(graph_t *graph)
{
    int path_length = find_shortest_path(graph);
    char **array = NULL;

    if (path_length == INT_MAX)
        return;
    array = malloc(sizeof(char *) * (path_length + 1));
    if (!array)
        return;
    if (graph->path->length_path[0] == path_length)
        fill_path_room(graph, path_length, array);
    array[path_length] = NULL;
    output_robots(graph, array);
    free_array(array);
}
