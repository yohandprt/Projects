##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/main.cpp \
		src/game/GameState.cpp \
		src/shape/AShape.cpp \
		src/shape/circle/ACircle.cpp \
		src/shape/rectangle/ARectangle.cpp \
		src/utils/DLHandler.cpp \
		src/utils/GameManager.cpp \
		src/menu/Menu.cpp \
		src/menu/Leaderboard.cpp \
		src/AGameModule.cpp \

ABSTRACT_SRC =	src/game/GameState.cpp \
				src/shape/AShape.cpp \
				src/shape/circle/ACircle.cpp \
				src/shape/rectangle/ARectangle.cpp \
				src/AGameModule.cpp \

SFML_SRC =	src/SFML/lib/ArcadeSfml.cpp \
			src/SFML/shape/circle/SfmlCircle.cpp \
			src/SFML/shape/rectangle/SfmlRectangle.cpp \
			src/SFML/sprite/SfmlSprite.cpp \

SDL_SRC =	src/SDL2/lib/ArcadeSdl.cpp \
			src/SDL2/shape/circle/SdlCircle.cpp \
			src/SDL2/shape/rectangle/SdlRectangle.cpp \
			src/SDL2/sprite/SdlSprite.cpp \

NCURSES_SRC =	src/NCURSES/lib/ArcadeNCurses.cpp \
				src/NCURSES/shape/circle/NCursesCircle.cpp \
				src/NCURSES/shape/rectangle/NCursesRectangle.cpp \
				src/NCURSES/sprite/NCursesSprite.cpp \

PACMAN_SRC =    game/pacman/packmangame.cpp \
				game/pacman/PacmanGameLogic.cpp \
				game/pacman/PacmanGameGraphics.cpp \
				game/pacman/PacmanMap.cpp \
				game/pacman/Character.cpp \
				game/pacman/PacmanGhost.cpp \
				game/pacman/PacmanGhostAlgo.cpp \
				game/pacman/GhostManager.cpp

SNAKE_SRC = game/Snake/Snake.cpp

MENU_SRC =		src/menu/Menu.cpp \
				src/menu/Leaderboard.cpp \
				src/utils/DLHandler.cpp \

LIB_DIR = ./lib/

SFML_NAME = $(LIB_DIR)arcade_sfml.so
SDL_NAME = $(LIB_DIR)arcade_sdl2.so
NCURSES_NAME = $(LIB_DIR)arcade_ncurses.so

SNAKE_NAME = $(LIB_DIR)arcade_snake.so
PACMAN_NAME = $(LIB_DIR)arcade_pacman.so

MENU_NAME = $(LIB_DIR)menu.so


NAME = arcade

NAME_DEBUG = debug.arcade

OBJ = $(SRC:.cpp=.o)

ABSTRACT_OBJ = $(ABSTRACT_SRC:.cpp=.o)
SFML_OBJ = $(SFML_SRC:.cpp=.o)
SDL_OBJ = $(SDL_SRC:.cpp=.o)
NCURSES_OBJ = $(NCURSES_SRC:.cpp=.o)

SNAKE_OBJ = $(SNAKE_SRC:.cpp=.o)
PACMAN_OBJ = $(PACMAN_SRC:.cpp=.o)

MENU_OBJ = $(MENU_SRC:.cpp=.o)

WARNINGS = -Wextra -Wall -Werror -std=c++20

CFLAGS = 	-fPIC -I./src -I./src/game -I./src/utils -I./src/shape -I./src/shape/circle -I./src/shape/rectangle -I./src/sprite -I./src/menu \
			-I./src/NCURSES/lib -I./src/NCURSES/shape/circle -I./src/NCURSES/shape/rectangle -I./src/NCURSES/sprite \
			-I./src/SDL2/lib -I./src/SDL2/shape/circle -I./src/SDL2/shape/rectangle -I./src/SDL2/sprite \
			-I./src/SFML/lib -I./src/SFML/shape/circle -I./src/SFML/shape/rectangle -I./src/SFML/sprite \
			-I./game -I./src/pacman

SFML_LIB_FLAGS =	-lsfml-graphics -lsfml-window -lsfml-system
SDL_LIB_FLAGS =		-lSDL2 -lSDL2_image -lSDL2_ttf
NCURSES_LIB_FLAGS =	-lncurses

CC = clang++

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS) $(WARNINGS)

all:	core graphicals games

$(NAME): 	$(OBJ) $(ABSTRACT_OBJ)
	$(CC) $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME)

$(NAME_DEBUG): $(OBJ)
	$(CC) -g $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME_DEBUG)

debug:	$(NAME_DEBUG) graphicals games
	valgrind ./$(NAME_DEBUG)

clean:
	rm -f $(OBJ) $(ABSTRACT_OBJ) $(SFML_OBJ) $(SDL_OBJ) $(NCURSES_OBJ) $(GAME1_OBJ) $(GAME2_OBJ) $(SNAKE_OBJ) $(PACMAN_OBJ) $(MENU_OBJ)

fclean: 	clean
	rm -f $(NAME) $(NAME_DEBUG) $(SFML_NAME) $(SDL_NAME) $(NCURSES_NAME) $(GAME1_NAME) $(GAME2_NAME) $(SNAKE_NAME) $(PACMAN_NAME) $(MENU_NAME)

re:	fclean all

core:	$(NAME)

graphicals:		$(ABSTRACT_OBJ) $(SFML_OBJ) $(SDL_OBJ) $(NCURSES_OBJ) $(MENU_OBJ)
	mkdir -p $(LIB_DIR)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(SFML_OBJ) $(CFLAGS) $(SFML_LIB_FLAGS) $(WARNINGS) -o $(SFML_NAME)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(SDL_OBJ) $(CFLAGS) $(SDL_LIB_FLAGS) $(WARNINGS) -o $(SDL_NAME)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(NCURSES_OBJ) $(CFLAGS) $(NCURSES_LIB_FLAGS) $(WARNINGS) -o $(NCURSES_NAME)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(MENU_OBJ) $(CFLAGS) $(WARNINGS) -o $(MENU_NAME)

games:		$(ABSTRACT_OBJ) $(SNAKE_OBJ) $(PACMAN_OBJ)
	mkdir -p $(LIB_DIR)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(SNAKE_OBJ) $(CFLAGS) $(WARNINGS) -o $(SNAKE_NAME)
	g++ -shared -fPIC $(ABSTRACT_OBJ) $(PACMAN_OBJ) $(CFLAGS) $(WARNINGS) -o $(PACMAN_NAME)

run:
	./$(NAME) $(SFML_NAME)

.PHONY: debug clean fclean re
