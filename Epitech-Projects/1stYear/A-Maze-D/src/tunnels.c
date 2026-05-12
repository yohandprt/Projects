/*
** EPITECH PROJECT, 2025
** tunnels.c
** File description:
** tunnels
*/

#include "amazed.h"

int get_nb_tunnels(graph_t *graph)
{
    int cpt = 0;

    for (int i = 0; graph->parse->lines[i]; i++) {
        if (is_tunnel(graph->parse->lines[i]))
            cpt++;
    }
    return cpt;
}
