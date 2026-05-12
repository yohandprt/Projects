/*
** EPITECH PROJECT, 2025
** free_graph.c
** File description:
** free_graph
*/

#include "amazed.h"

static void free_move(graph_t *graph)
{
    if (!graph || !graph->move)
        return;
    if (graph->move->positions)
        free(graph->move->positions);
    free(graph->move);
}

static void free_all_path(graph_t *graph)
{
    for (int i = 0; i < graph->path->nb_path; i++)
        free(graph->path->all_path[i]);
    free(graph->path->all_path);
}

void free_path(graph_t *graph)
{
    if (!graph || !graph->path)
        return;
    if (graph->path->length_path)
        free(graph->path->length_path);
    if (graph->path->all_path)
        free_all_path(graph);
    free(graph->path);
}

void free_parse(graph_t *graph)
{
    if (!graph)
        return;
    if (graph->parse) {
        if (graph->parse->lines)
            free_array(graph->parse->lines);
        if (graph->parse->tunnels)
            free_array(graph->parse->tunnels);
        if (graph->parse->all_rooms)
            free_array(graph->parse->all_rooms);
        if (graph->parse->output_rooms)
            free_array(graph->parse->output_rooms);
        free(graph->parse);
    }
}

void free_graph(graph_t *graph)
{
    if (!graph)
        return;
    if (graph->starts)
        free(graph->starts);
    if (graph->ends)
        free(graph->ends);
    free_parse(graph);
    free_move(graph);
    free_path(graph);
    if (graph->rooms) {
        for (int i = 0; i < graph->nb_rooms; i++)
            free(graph->rooms[i]);
        free(graph->rooms);
    }
    if (graph->matrice) {
        for (int i = 0; i < graph->nb_rooms + 1; i++)
            free(graph->matrice[i]);
        free(graph->matrice);
    }
    free(graph);
}

int free_and_return(char **numbers, char *line, int nb_return)
{
    if (numbers) {
        free_array(numbers);
        numbers = NULL;
    }
    if (line) {
        free(line);
        line = NULL;
    }
    return nb_return;
}

void free_and_void(char **numbers, char *line)
{
    if (numbers) {
        free_array(numbers);
        numbers = NULL;
    }
    if (line) {
        free(line);
        line = NULL;
    }
}
