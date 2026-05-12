##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/main.cpp \
		src/Utils.cpp \
		src/AComponent.cpp \
		src/ComponentFactory.cpp \
		src/InputComponent.cpp \
		src/OutputComponent.cpp \
		src/TrueComponent.cpp \
		src/FalseComponent.cpp \
		src/ClockComponent.cpp \
		src/LoggerComponent.cpp \
		src/Link.cpp \
		src/AndComponent.cpp \
		src/OrComponent.cpp \
		src/XorComponent.cpp \
		src/NotComponent.cpp \
		src/AdderComponent.cpp \
		src/CounterComponent.cpp \
		src/DecoderComponent.cpp \
		src/FlipFlopComponent.cpp \
		src/RomComponent.cpp \
		src/RamComponent.cpp \
		src/JohnsonComponent.cpp \
		src/SelectorComponent.cpp \
		src/ShiftComponent.cpp \
		src/4001.cpp \
		src/4011.cpp \
		src/4030.cpp \
		src/4069.cpp \
		src/4071.cpp \
		src/4081.cpp \
		src/Circuit.cpp \
		src/Shell.cpp \
		src/Parser.cpp

NAME = nanotekspice

NAME_DEBUG = debug.nanotekspice

OBJ = $(SRC:.cpp=.o)

WARNINGS = -Wextra -Wall -Werror -std=c++20

CFLAGS = -Iinclude

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS) $(WARNINGS)

$(NAME): 	$(OBJ)
	clang++ $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME)

$(NAME_DEBUG): $(OBJ)
	clang++ -g $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME_DEBUG)

all:	$(NAME)

debug:	$(NAME_DEBUG)
	valgrind ./$(NAME_DEBUG)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME) $(NAME_DEBUG)

re:	fclean all

.PHONY: debug clean fclean re
