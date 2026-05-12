/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-thomas.villot
** File description:
** link.c
*/

#include "amazed.h"

int link_with_start(graph_t *graph)
{
    int connections = 0;
    int start_room = graph->starts[0] - 48;

    if (start_room == -1)
        return 84;
    for (int i = 0; i < graph->nb_rooms; i++) {
        if (graph->matrice[start_room][i] == 1 && i != start_room) {
            connections++;
        }
    }
    return connections;
}

int link_with_end(graph_t *graph)
{
    int connections = 0;
    int end_room = graph->ends[0] - 48;

    if (end_room == -1)
        return 84;
    for (int i = 0; i < graph->nb_rooms; i++) {
        if (graph->matrice[end_room][i] == 1 && i != end_room) {
            connections++;
        }
    }
    return connections;
}
