##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	amazed.c \
    src/handle_matrice.c \
    src/init_graph.c \
    src/free_graph.c \
    src/output.c \
    src/starts_ends.c \
    src/tunnels.c \
    src/error_handling.c \
    src/parsing.c \
    src/filling.c \
    src/filling2.c \
    src/file.c \
    src/link.c \
	src/algo.c 		\
	src/sort_path.c \
	src/moves.c \
	src/display_move_robots.c \

LIB = libmy.a

NAME = amazed

NAME_DEBUG = amazed

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

WARNINGS = -Wextra -Wall -Werror -g

CFLAGS = -I./include -L./lib -lmy -g

$(NAME): 	$(LIB) $(OBJ_DIR) $(OBJ)
	gcc $(OBJ) -o $(NAME) $(CFLAGS) $(WARNINGS)

$(NAME_DEBUG): $(LIB) $(OBJ_DIR) $(OBJ)
	gcc -g $(OBJ) -o $(NAME) $(CFLAGS) $(WARNINGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/src

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc $(WARNINGS) -c $< -o $@ -I./include

$(LIB):
	make -C lib/my

all:	$(NAME)

debug:	$(NAME_DEBUG)
	valgrind ./$(NAME_DEBUG)

clean:
	rm -rf $(OBJ_DIR)
	make -C lib/my clean

fclean: 	clean
	rm -f $(NAME)
	make -C lib/my fclean

re:	fclean all

.PHONY: clean fclean re $(OBJ_DIR)
