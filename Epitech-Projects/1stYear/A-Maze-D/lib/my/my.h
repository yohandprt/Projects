/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my header
*/

#ifndef MY_H
    #define MY_H

    #include <stddef.h>
    #include <stdarg.h>
    #include <dirent.h>

typedef enum type {
    CHAR,
    STRING,
    INTEGER,
    FLOAT
} type_t;
typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
} linked_list_t;
linked_list_t *create_list(void *data);
void add_to_list(linked_list_t **list, void *data, int pos);
void rm_to_list(linked_list_t **list, int pos);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_isneg(int n);
int divi(int nb, int divisible);
int my_is_prime(int nb);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
char *my_revstr(char *str);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
void my_sort_int_array(int *tab, int size);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
int my_str_isalpha(char const *str);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
char **str_to_array(char *buffer, char *separator);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
void my_swap(int *a, int *b);
int my_put_float(double nb, int precision);
int my_put_octal(int nb);
int my_put_unsigned_nbr(int nb);
int my_put_hexa(int nb, int majuscule);
int my_put_pointer(void *p);
int my_put_e(double nb, int majuscule);
int my_put_g(double nb, int majuscule);
int my_put_signed_long(long nb);
int my_put_signed_longlong(long long nb);
void my_printf(char const *format, ...);
int case_g(char const *format, va_list args, int i);
int case_e(char const *format, va_list args, int i);
int case_fi(char const *format, va_list args, int i);
int case_ou(char const *format, va_list args, int i);
int case_p(char const *format, va_list args, int i);
int case_cpourcent(char const *format, va_list args, int i);
int case_sd(char const *format, va_list args, int i);
int case_x(char const *format, va_list args, int i);
int my_put_unsigned_long(long nb);
int my_put_unsigned_longlong(long long nb);
int case_l(char const *format, va_list args, int i);
int my_str_to_int(char const *str);
int find_number(char const *format, int debut);
int my_put_minus(int nb, int decalage);
int case_minus(char const *format, va_list args, int i);
int my_put_plus(int nb, int decal);
int case_plus(char const *format, va_list args, int i);
int my_put_zero(int nb, int decal);
int case_zero(char const *format, va_list args, int i);
int count_int(int nb);
char my_charlowcase(char c);
void my_sort_str_array(char **array);
void my_rev_array(char **array);
char *my_int_to_str(int nb);
int my_arraylen(char **array);
int count_lines(char *str_map);
int count_columns(char *str_map, int nb);
void replace(char **map, int start_i, int start_j, int side_size);
void display(char **map, int lines, int columns);
int check_square(char **map, int start_i, int start_j, int side_size);
void display_perm(char *path_file, char *file);
char *add_arguments(char **argv, char **paths, char *args, int argc);
int my_getloadavg(double loadavg[], int nelem);
int my_puterr(char const *str);
char *my_decstr(char *str, int left, int right);
int comp_str_array(char *s1, char **array);
void print_array(char **array, char *separator);
void free_array(char **array);
int get_size(char *file);
char *get_file(char *file);
char **cp_array(char **array);
char *my_strdup(char const *src);
char **str_array_deli(char const *str, char const *deli);
int my_isdigit(char c);
#endif
