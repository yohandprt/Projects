/*
** EPITECH PROJECT, 2025
** init_graph.c
** File description:
** init_graph
*/

#include "amazed.h"

static int get_nb_robots(graph_t *graph)
{
    int nb = 0;
    int i = 0;

    for (; graph->parse->lines[i]; i++) {
        if (graph->parse->lines[i][0] == '#')
            continue;
        if (!is_num(graph->parse->lines[i]))
            return -1;
        else
            break;
    }
    graph->parse->ind_robots = i;
    nb = my_str_to_int(graph->parse->lines[i]);
    return nb;
}

static int get_nb_rooms(graph_t *graph)
{
    int cpt = 0;

    for (int i = 0; graph->parse->lines[i]; i++) {
        if (is_room(graph->parse->lines[i]))
            cpt++;
    }
    if (cpt == 0)
        graph->parse->no_rooms = 1;
    return cpt;
}

static void fill_all(graph_t *graph)
{
    fill_matrice(graph);
    fill_starts(graph, 0);
    fill_all_rooms(graph, 0);
    fill_ends(graph, 0);
    fill_tunnels(graph);
    fill_output_rooms(graph, 0);
}

static parse_t *init_parse(void)
{
    parse_t *parse = malloc(sizeof(parse_t));

    if (!parse)
        return NULL;
    parse->output_rooms = NULL;
    parse->all_rooms = NULL;
    parse->tunnels = NULL;
    parse->no_start = 0;
    parse->no_rooms = 0;
    parse->no_end = 0;
    parse->lines = read_file();
    return parse;
}

int init_values(graph_t *graph)
{
    graph->starts = NULL;
    graph->rooms = NULL;
    graph->ends = NULL;
    graph->matrice = NULL;
    graph->move = NULL;
    graph->path = NULL;
    graph->parse = init_parse();
    graph->nb_robots = get_nb_robots(graph);
    if (!graph->parse->lines || graph->nb_robots == -1 || !graph->parse)
        return 84;
    graph->nb_rooms = get_nb_rooms(graph);
    graph->rooms = malloc(sizeof(rooms_t) * (graph->nb_rooms + 1));
    for (int i = 0; i < graph->nb_rooms; i++)
        graph->rooms[i] = malloc(sizeof(rooms_t));
    return 0;
}

graph_t *init_graph(void)
{
    graph_t *graph = malloc(sizeof(graph_t));

    if (init_values(graph) == 84)
        return return_error(graph, 0);
    if (verif_file(graph, graph->parse->lines, 0, 0) == 84)
        return return_error(graph, 0);
    if (graph->parse->no_rooms)
        return return_error(graph, 1);
    fill_all(graph);
    if (!graph->starts || !graph->ends)
        return return_error(graph, 1);
    if (!graph->matrice ||
        !graph->parse->tunnels || !graph->parse->output_rooms)
        return return_error(graph, 0);
    fill_rooms(graph);
    if (!graph->rooms)
        return return_error(graph, 0);
    return graph;
}
