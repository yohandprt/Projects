##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =		src/Socket.cpp \
			src/Helper.cpp \

SRC_SRV =	src/main_server.cpp \
			src/Server.cpp \
			src/User.cpp \
			src/CommandHandler.cpp \
			src/CommandParser.cpp \
			src/ServerState.cpp \
			src/Team.cpp \
			src/Channel.cpp \
			src/Thread.cpp \
			src/AMessage.cpp \
			src/AIdentifiable.cpp \
			src/UUID.cpp \
			src/Loader.cpp \
			src/Saver.cpp \

SRC_CLI =	src/main_cli.cpp \
			src/Client.cpp \
			src/EventClientHandler.cpp \
			src/CommandParser.cpp \



NAME_SRV = myteams_server
NAME_CLI = myteams_cli

NAME_DEBUG_SRV = debug.myteams_server
NAME_DEBUG_CLI = debug.myteams_cli

OBJ = $(SRC:.cpp=.o)
OBJ_SRV = $(SRC_SRV:.cpp=.o)
OBJ_CLI = $(SRC_CLI:.cpp=.o)

WARNINGS = -Wextra -Wall -Werror -std=c++20

LIB_DIR = libs/myteams

CFLAGS =	-I./include -I./libs/myteams
LDFLAGS =	-L$(LIB_DIR) -lmyteams

CC = clang++

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(WARNINGS)

all:	$(NAME_SRV) $(NAME_CLI)

$(NAME_SRV): 	$(OBJ) $(OBJ_SRV)
	$(CC) $(OBJ) $(OBJ_SRV) $(LDFLAGS) -o $(NAME_SRV)

$(NAME_CLI): 	$(OBJ) $(OBJ_CLI)
	$(CC) $(OBJ) $(OBJ_CLI) $(LDFLAGS) -o $(NAME_CLI)


$(NAME_DEBUG_SRV): $(OBJ) $(OBJ_SRV)
	$(CC) -g $(CFLAGS) $(WARNINGS) $(OBJ) $(OBJ_SRV) -ldl -Wl,-rpath=./lib -o $(NAME_DEBUG_SRV)

$(NAME_DEBUG_CLI): $(OBJ) $(OBJ_CLI)
	$(CC) -g $(CFLAGS) $(WARNINGS) $(OBJ) $(OBJ_CLI) -ldl -Wl,-rpath=./lib -o $(NAME_DEBUG_CLI)

debug:	$(NAME_DEBUG_SRV) $(NAME_DEBUG_CLI)
	valgrind ./$(NAME_DEBUG_SRV)

clean:
	rm -f $(OBJ) $(OBJ_SRV) $(OBJ_CLI)

fclean: 	clean
	rm -f $(NAME_SRV) $(NAME_CLI) $(NAME_DEBUG_SRV) $(NAME_DEBUG_CLI)

re:	fclean all

server: $(NAME_SRV)

client: $(NAME_CLI)

.PHONY: debug clean fclean re
