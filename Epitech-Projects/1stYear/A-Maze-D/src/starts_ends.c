/*
** EPITECH PROJECT, 2025
** handle_starts_ends.c
** File description:
** handle_starts_ends
*/

#include "amazed.h"

int find_starter(graph_t *graph, char *to_find, int *nb, int i)
{
    if (!to_find || !graph || !nb)
        return 0;
    if (my_strcmp(graph->parse->lines[i], to_find) == 0) {
        *nb = 1;
        return 1;
    }
    return 0;
}

int count_rooms(graph_t *graph)
{
    int cpt = 0;

    if (!graph)
        return -1;
    for (int i = graph->parse->ind_robots + 1; graph->parse->lines[i]; i++) {
        if ((graph->parse->lines[i][0] != '#'
                && !is_room(graph->parse->lines[i])))
            break;
        if (is_room(graph->parse->lines[i]) && (graph->parse->lines[i - 1] &&
                verif_title(graph->parse->lines[i - 1])))
            cpt++;
    }
    return cpt;
}
