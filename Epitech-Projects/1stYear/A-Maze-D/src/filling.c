/*
** EPITECH PROJECT, 2025
** filling.c
** File description:
** filling
*/

#include "amazed.h"

void fill_starts(graph_t *graph, int st)
{
    int ind = 0;

    graph->starts = NULL;
    for (int i = 0; graph->parse->lines[i]; i++) {
        if (find_starter(graph, "##start", &st, i))
            continue;
        if (st && ((graph->parse->lines[i][0] == '#' &&
                graph->parse->lines[i][1] == '#') ||
                    (graph->parse->lines[i][0] != '#' &&
                !is_room(graph->parse->lines[i]))))
            break;
        if (st && graph->parse->lines[i][0] != '#' &&
                is_room(graph->parse->lines[i])) {
            graph->starts = remove_comment(graph->parse->lines[i]);
            ind++;
            break;
        }
    }
    if (ind == 0)
        graph->starts = NULL;
}

void fill_ends(graph_t *graph, int end)
{
    int ind = 0;

    graph->ends = NULL;
    for (int i = 0; graph->parse->lines[i]; i++) {
        if (find_starter(graph, "##end", &end, i))
            continue;
        if (end && ((graph->parse->lines[i][0] == '#' &&
                graph->parse->lines[i][1] == '#') ||
            (graph->parse->lines[i][0] != '#' &&
                    !is_room(graph->parse->lines[i]))))
            break;
        if (end && graph->parse->lines[i][0] != '#' &&
                is_room(graph->parse->lines[i])) {
            graph->ends = remove_comment(graph->parse->lines[i]);
            ind++;
            break;
        }
    }
    if (ind == 0)
        graph->ends = NULL;
}

void fill_all_rooms(graph_t *graph, int ind)
{
    graph->parse->all_rooms = malloc(sizeof(char *) * (graph->nb_rooms + 1));
    for (int i = graph->parse->ind_robots + 1; graph->parse->lines[i]; i++) {
        if (graph->parse->lines[i][0] != '#' &&
                !is_room(graph->parse->lines[i]))
            break;
        if (is_room(graph->parse->lines[i]) && (graph->parse->lines[i - 1] &&
                verif_title(graph->parse->lines[i - 1]))) {
            graph->parse->all_rooms[ind] =
                remove_comment(graph->parse->lines[i]);
            ind++;
        }
    }
    graph->parse->all_rooms[ind] = NULL;
    if (ind == 0) {
        free(graph->parse->all_rooms);
        graph->parse->all_rooms = NULL;
    }
}

void fill_output_rooms(graph_t *graph, int ind)
{
    graph->parse->output_rooms = malloc(sizeof(char *) *
        (graph->nb_rooms + 4));
    for (int i = graph->parse->ind_robots + 1; graph->parse->lines[i]; i++) {
        if (((graph->parse->lines[i][0] != '#' &&
                !is_room(graph->parse->lines[i]))))
            break;
        if (is_room(graph->parse->lines[i])) {
            graph->parse->output_rooms[ind] =
                remove_comment(graph->parse->lines[i]);
            ind++;
        }
        if (!verif_title(graph->parse->lines[i])) {
            graph->parse->output_rooms[ind] =
                my_strdup(graph->parse->lines[i]);
            ind++;
        }
    }
    graph->parse->output_rooms[ind] = NULL;
    if (ind == 0)
        graph->parse->output_rooms = NULL;
}

void fill_tunnels(graph_t *graph)
{
    int ind = 0;
    int nb_tunnels = get_nb_tunnels(graph);

    graph->parse->tunnels = malloc(sizeof(char *) * (nb_tunnels + 1));
    for (int i = 0; graph->parse->lines[i]; i++) {
        if (is_tunnel(graph->parse->lines[i])) {
            graph->parse->tunnels[ind] =
                remove_comment(graph->parse->lines[i]);
            ind++;
        }
    }
    graph->parse->tunnels[ind] = NULL;
    if (ind == 0) {
        free(graph->parse->tunnels);
        graph->parse->tunnels = NULL;
    }
}
