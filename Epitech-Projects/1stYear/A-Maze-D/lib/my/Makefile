##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = printf/my_put_unsigned_nbr.c \
      printf/my_put_octal.c \
      printf/my_put_float.c \
      printf/my_put_hexa.c \
      printf/my_put_pointer.c \
      printf/my_put_e.c \
      printf/my_put_g.c \
      printf/my_put_signed_long.c \
      printf/my_put_signed_longlong.c \
      printf/my_put_unsigned_long.c \
      printf/my_put_unsigned_longlong.c \
      printf/my_put_minus.c \
      printf/my_put_plus.c \
      printf/my_put_zero.c \
      printf/case_e.c \
      printf/case_fi.c \
      printf/case_g.c \
      printf/case_l.c \
      printf/case_minus.c \
      printf/case_ou.c \
      printf/case_p.c \
      printf/case_plus.c \
      printf/case_pourcent.c \
      printf/case_sd.c \
      printf/case_x.c \
      printf/case_zero.c \
      my_printf.c \
      mal_strcat.c \
      mini_printf.c \
      my_getnbr.c \
      my_isneg.c \
      my_putchar.c \
      my_put_nbr.c \
      my_putstr.c \
      my_realloc.c \
      my_revstr.c \
      my_sort_int_array.c \
      my_strcat.c \
      my_strcmp.c \
      my_strcpy.c \
      my_strdup.c \
      my_strlen.c \
      my_strlowcase.c \
      my_strncat.c \
      my_strncmp.c \
      my_strncpy.c \
      my_str_to_word_delimiter.c \
      my_strupcase.c \
      my_swap.c \
      my_str_to_int.c \
      print_array.c \
      find_nbr.c \
      count_int.c \
      my_isdigit.c \
      my_strstr.c \
      free_array.c \
      my_arraylen.c \
      my_int_to_str.c \

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME):        $(OBJ)
	ar rc ../$(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean $(NAME)
