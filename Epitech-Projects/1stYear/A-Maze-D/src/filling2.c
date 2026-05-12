/*
** EPITECH PROJECT, 2025
** filling2.c
** File description:
** filling
*/

#include "amazed.h"

void free_split_room(char **split_room)
{
    free_array(split_room);
    split_room = NULL;
}

void fill_room(graph_t *graph, char *str, int i)
{
    char **split_room = NULL;

    if (!str) {
        graph->rooms[i] = NULL;
        return;
    }
    split_room = str_array_deli(str, " ");
    graph->rooms[i]->num = my_str_to_int(split_room[0]);
    graph->rooms[i]->x = my_str_to_int(split_room[1]);
    graph->rooms[i]->y = my_str_to_int(split_room[2]);
    free_split_room(split_room);
}

void fill_rooms(graph_t *graph)
{
    int i = 0;

    if (graph->parse->all_rooms) {
        for (; graph->parse->all_rooms[i]; i++)
            fill_room(graph, graph->parse->all_rooms[i], i);
    }
    if (!(graph->parse->no_start || graph->parse->no_end)) {
        fill_room(graph, graph->starts, i);
        fill_room(graph, graph->ends, i + 1);
        graph->rooms[i + 2] = NULL;
    } else
        graph->rooms[i] = NULL;
    return;
}
