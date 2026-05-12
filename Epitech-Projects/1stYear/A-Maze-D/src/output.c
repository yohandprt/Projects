/*
** EPITECH PROJECT, 2025
** output.c
** File description:
** output
*/

#include "amazed.h"

void display_robots(graph_t *graph)
{
    my_printf("#number_of_robots\n%d\n", graph->nb_robots);
}

void display_rooms(graph_t *graph)
{
    my_printf("#rooms\n");
    if (!graph->parse->no_rooms) {
        print_array(graph->parse->output_rooms, "\n");
        my_printf("\n");
        if (!(graph->parse->no_start || graph->parse->no_end)) {
            my_printf("#tunnels\n");
            print_array(graph->parse->tunnels, "\n");
            my_printf("\n#moves\n");
        }
    }
}

void output(graph_t *graph)
{
    display_robots(graph);
    display_rooms(graph);
}
