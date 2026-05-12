/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** globbing_utils.c
*/

#include "shell.h"
#include "globbing.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <fnmatch.h>

int has_wildcard(const char *str)
{
    if (!str)
        return 0;
    for (int j = 0; str[j] != '\0'; j++)
        if (str[j] == '*' || str[j] == '?' ||
            str[j] == '[' || str[j] == ']')
            return 1;
    return 0;
}

void free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

int count_array(const char *dir_path, const char *pattern)
{
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    int count = 0;

    if (!dir || !pattern)
        return 0;
    entry = readdir(dir);
    while (entry != NULL) {
        if (fnmatch(pattern, entry->d_name, 0) == 0)
            count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}

static char *create_full_path(const char *dir_path, const char *file_name)
{
    char *full_path = malloc(strlen(dir_path) + strlen(file_name) + 2);

    if (!full_path)
        return NULL;
    snprintf(full_path, strlen(dir_path) + strlen(file_name) + 2,
        "%s/%s", dir_path, file_name);
    return full_path;
}

static void add_to_array(char **array, const char *dir_path,
    struct dirent *entry, int *index)
{
    if (strcmp(dir_path, ".") == 0) {
        array[*index] = strdup(entry->d_name);
    } else {
        array[*index] = create_full_path(dir_path, entry->d_name);
    }
    if (!array[*index]) {
        free_tab(array);
        return;
    }
    (*index)++;
}

static DIR *open_directory(const char *dir_path, char **array)
{
    DIR *dir = opendir(dir_path);

    if (!dir) {
        free_tab(array);
        return NULL;
    }
    return dir;
}

char **fill_array(const char *dir_path, const char *pattern, int count)
{
    DIR *dir = open_directory(dir_path, NULL);
    struct dirent *entry;
    char **array = malloc(sizeof(char *) * (count + 1));
    int index = 0;

    if (!array || !dir) {
        if (dir)
            closedir(dir);
        return NULL;
    }
    entry = readdir(dir);
    while (entry != NULL) {
        if (fnmatch(pattern, entry->d_name, 0) == 0)
            add_to_array(array, dir_path, entry, &index);
        entry = readdir(dir);
    }
    array[index] = NULL;
    closedir(dir);
    return array;
}

char **get_pattern(const char *pattern)
{
    char path[1024] = {0};
    char *last_slash = strrchr(pattern, '/');
    char **array = NULL;
    int count = 0;

    if (!pattern)
        return NULL;
    if (last_slash) {
        strncpy(path, pattern, last_slash - pattern);
        path[last_slash - pattern] = '\0';
        pattern = last_slash + 1;
    } else {
        strcpy(path, ".");
    }
    count = count_array(path, pattern);
    if (count == 0)
        return NULL;
    array = fill_array(path, pattern, count);
    return array;
}
