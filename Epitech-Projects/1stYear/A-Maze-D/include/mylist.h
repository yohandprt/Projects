/*
** EPITECH PROJECT, 2024
** mylist.h
** File description:
** mylist
*/
#ifndef MY_LIST
    #define MY_LIST

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

#endif
