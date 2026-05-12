/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** algo.c
*/

#include "amazed.h"
#include <stdbool.h>

static void print_link(int j, int i, graph_t *graph)
{
    if (j != graph->path->length_path[i] -1)
        my_printf(" -> ");
}

void display_path(graph_t *graph)
{
    my_printf("Numbers of path: %d\n", graph->path->nb_path);
    for (int i = 0; i < graph->path->nb_path; i++) {
        for (int j = 0; j < graph->path->length_path[i]; j++) {
            my_printf("%d", graph->path->all_path[i][j]);
            print_link(j, i, graph);
        }
        my_printf("  length: %d", graph->path->length_path[i]);
        my_printf("\n");
    }
}

static int get_start(char *str)
{
    char **array = str_array_deli(str, " ");
    int start = 0;

    if (array) {
        start = my_getnbr(array[0]);
        free_array(array);
    }
    return start;
}

static int get_end(char *str)
{
    char **array = str_array_deli(str, " ");
    int end = 0;

    if (array) {
        end = my_getnbr(array[0]);
        free_array(array);
    }
    return end;
}

void save_found_path(graph_t *graph, int *path, int index)
{
    int path_idx = graph->path->nb_path;

    if (graph->path->min_length == 0 || index + 1 < graph->path->min_length)
        graph->path->min_length = index + 1;
    graph->path->all_path = my_realloc(graph->path->all_path,
        sizeof(int *) * path_idx, sizeof(int *) * (path_idx + 1));
    graph->path->all_path[path_idx] = malloc(sizeof(int) * (index + 1));
    for (int i = 0; i <= index; i++)
        graph->path->all_path[path_idx][i] = path[i];
    graph->path->length_path = my_realloc(graph->path->length_path,
        sizeof(int) * path_idx, sizeof(int) * (path_idx + 1));
    graph->path->length_path[path_idx] = index + 1;
    graph->path->nb_path++;
}

void explore_room(graph_t *graph, int **old_path, int visited[], int index)
{
    int current = graph->path->current;

    if (graph->path->min_length > 0 && index + 1 >= graph->path->min_length)
        return;
    for (int i = 0; i < graph->nb_rooms; i++) {
        if (graph->matrice[current][i] == 1 && visited[i] != 1) {
            graph->path->current = i;
            dfs(graph, old_path, visited, index + 1);
        }
    }
}

void dfs(graph_t *graph, int **old_path, int visited[], int index)
{
    int end = get_end(graph->ends);
    int current = graph->path->current;
    int *path = *old_path;

    if (graph->path->min_length > 0 && index >= graph->path->min_length)
        return;
    visited[current] = 1;
    path = my_realloc(path, sizeof(int) * index, sizeof(int) * (index + 1));
    *old_path = path;
    path[index] = current;
    if (current == end)
        save_found_path(graph, path, index);
    else
        explore_room(graph, old_path, visited, index);
    visited[current] = 0;
}

void find_all_path(graph_t *graph)
{
    int start = get_start(graph->starts);
    int *path = malloc(sizeof(int));
    int visited[graph->nb_rooms];

    for (int i = 0; i < graph->nb_rooms; i++)
        visited[i] = 0;
    graph->path = malloc(sizeof(path_t));
    if (!graph->path || !path)
        return;
    graph->path->min_length = 99999;
    graph->path->all_path = malloc(sizeof(int *));
    graph->path->length_path = malloc(sizeof(int));
    graph->path->nb_path = 0;
    graph->path->current = start;
    graph->path->i = 0;
    dfs(graph, &path, visited, 0);
    free(path);
}
