/*
** EPITECH PROJECT, 2025
** handle_matrice.c
** File description:
** handle_matrice
*/

#include "amazed.h"

void print_matrice(graph_t *graph)
{
    int j = 0;

    for (int i = 0; i < graph->nb_rooms; i++) {
        for (j = 0; j < graph->nb_rooms - 1; j++)
            my_printf("%d ", graph->matrice[i][j]);
        my_printf("%d\n", graph->matrice[i][j]);
    }
}

void get_len_nbr(char *line, int *len_first, int *len_last)
{
    int dash = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '-') {
            dash = 1;
            continue;
        }
        if (!(dash))
            (*len_first)++;
        if (dash)
            (*len_last)++;
    }
}

// pour inverser la matrice faire : graph->matrice[lnb][fnb] = 1;
// à la place de graph->matrice[fnb][lnb] = 1; (avant derniere ligne)
void increase(graph_t *graph, char *line)
{
    char **numbers = NULL;
    char *new_line = NULL;
    int fnb = 0;
    int lnb = 0;

    if (!graph || !line)
        return;
    new_line = remove_comment(line);
    numbers = str_array_deli(new_line, "-");
    if (!numbers)
        return free_and_void(NULL, new_line);
    if (my_arraylen(numbers) != 2)
        return free_and_void(numbers, new_line);
    fnb = my_str_to_int(numbers[0]);
    lnb = my_str_to_int(numbers[1]);
    if (fnb > graph->nb_rooms || lnb > graph->nb_rooms)
        return free_and_void(numbers, new_line);
    graph->matrice[fnb][lnb] = 1;
    graph->matrice[lnb][fnb] = 1;
    free_and_void(numbers, new_line);
}

void diago(graph_t *graph, int i, int j)
{
    if (i == j)
        graph->matrice[i][j] = 1;
    else
        graph->matrice[i][j] = 0;
}

void fill_matrice(graph_t *graph)
{
    graph->matrice = malloc(sizeof(int *) * (graph->nb_rooms + 1));
    for (int i = 0; i <= graph->nb_rooms; i++) {
        graph->matrice[i] = malloc(sizeof(int) * (graph->nb_rooms + 1));
        for (int j = 0; j <= graph->nb_rooms; j++)
            diago(graph, i, j);
    }
    for (int i = 0; graph->parse->lines[i]; i++) {
        if (is_tunnel(graph->parse->lines[i]))
            increase(graph, graph->parse->lines[i]);
    }
}
