/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** utils.h
*/

#include "shell.h"

#ifndef UTILS_H_
    #define UTILS_H_

    #define GREEN "\033[92m"
    #define TURQUOISE "\033[36m"
    #define BLUE "\033[96m"
    #define RESET "\033[0m"

/* Utils */
char **my_str_to_word_array(const char *str, const char *delimiter);
char **parse_input(char *input);
void free_array(char **array);
char **resize_array(char **old_array, int old_size, int new_size);
void display_prompt(env_node_t *env_list);
void free_array(char **array);
char **my_strtok(char *str, char *delimiters);
char *read_file(char *file_name);
int my_arraylen(char **array);
int find_closing_quote(char *input, int *i, char quote_char, int start);

#endif
