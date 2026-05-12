/*
** EPITECH PROJECT, 2025
** display_move_robots
** File description:
** display_move_robots
*/

#include "amazed.h"

void add_end_robots(graph_t *graph, int i, int len, int *end)
{
    if (graph->move->positions[i] == len - 1)
        (*end)++;
}

void check_can_move(graph_t *graph, int i)
{
    for (int k = 0; k < graph->nb_robots; k++) {
        if (k != i && graph->move->positions[k] == graph->move->next_pos) {
            graph->move->can_move = 0;
            break;
        }
    }
}

void process(graph_t *graph, int len, int *end, char **path_rooms)
{
    for (int i = 0; i < graph->nb_robots; i++) {
        if (graph->move->positions[i] == len - 1)
            continue;
        graph->move->next_pos = graph->move->positions[i] + 1;
        graph->move->can_move = 1;
        if (graph->move->next_pos != 0 && graph->move->next_pos != len - 1)
            check_can_move(graph, i);
        if (graph->move->can_move) {
            graph->move->positions[i]++;
            my_printf("P%d", i + 1);
            my_printf("-%s ", path_rooms[graph->move->positions[i]]);
            add_end_robots(graph, i, len, end);
        }
    }
}

void output_robots(graph_t *graph, char **path_rooms)
{
    int len = my_arraylen(path_rooms);
    int end = 0;

    graph->move = malloc(sizeof(move_t));
    graph->move->next_pos = 0;
    graph->move->can_move = 0;
    graph->move->positions = malloc(sizeof(int) * graph->nb_robots);
    for (int i = 0; i < graph->nb_robots; i++)
        graph->move->positions[i] = 0;
    while (end < graph->nb_robots) {
        process(graph, len, &end, path_rooms);
        my_printf("\n");
    }
}
