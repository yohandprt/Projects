/*
** EPITECH PROJECT, 2025
** amazed.h
** File description:
** amazed
*/

#ifndef _AMAZED_H_
    #define _AMAZED_H_
    #include "my.h"
    #include <sys/types.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

typedef struct path_s {
    int **all_path;
    int *length_path;
    int min_length;
    int nb_path;
    int current;
    int i;
} path_t;
typedef struct move_s {
    int *positions;
    int can_move;
    int next_pos;
} move_t;
typedef struct rooms_s {
    int num;
    int x;
    int y;
} rooms_t;
typedef struct parse_s {
    int no_start;
    int no_end;
    int no_rooms;
    int ind_robots;
    char **output_rooms;
    char **tunnels;
    char **lines;
    char **all_rooms;
} parse_t;
typedef struct graph_s {
    parse_t *parse;
    rooms_t **rooms;
    int **matrice;
    char *starts;
    char *ends;
    int nb_robots;
    int nb_rooms;
    path_t *path;
    move_t *move;
} graph_t;
char **read_file(void);
void fill_matrice(graph_t *graph);
graph_t *init_graph(void);
void print_matrice(graph_t *graph);
void free_graph(graph_t *graph);
void fill_starts(graph_t *graph, int st);
void fill_all_rooms(graph_t *graph, int ind);
void fill_rooms(graph_t *graph);
void fill_ends(graph_t *graph, int end);
void fill_output_rooms(graph_t *graph, int ind);
void fill_tunnels(graph_t *graph);
void find_all_path(graph_t *graph);
void display_path(graph_t *graph);
void dfs_next(graph_t *graph, int index, int visited[], int path[]);
void dfs(graph_t *graph, int **path_ptr, int visited[], int index);
graph_t *return_error(graph_t *graph, int display);
char *remove_comment(char *str);
void output(graph_t *graph);
void display_rooms(graph_t *graph);
int is_num(char *str);
int is_room(char *line);
int is_tunnel(char *line);
int verif_file(graph_t *graph, char **lines, int start, int end);
int verif_title(char *line);
int find_starter(graph_t *graph, char *to_find, int *nb, int i);
int count_rooms(graph_t *graph);
int get_nb_tunnels(graph_t *graph);
int free_and_return(char **numbers, char *line, int nb_return);
void free_and_void(char **numbers, char *line);
int link_with_start(graph_t *graph);
int link_with_end(graph_t *graph);
void sort_path(graph_t *graph);
void display_robot_moves(graph_t *graph);
void print_robot_movements(graph_t *graph);
int move_robots(graph_t *graph);
void process_paths_directly(graph_t *graph);
void output_robots(graph_t *graph, char **path_rooms);
void display_path(graph_t *graph);
#endif
