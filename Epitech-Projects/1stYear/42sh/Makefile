##
## EPITECH PROJECT, 2025
## B-PSU-200-LIL-2-1-42sh-thomas.villot
## File description:
## Makefile for the 42sh project
##

SRC_MAIN	=	src/main.c

SRC_CORE	=	src/shell.c

SRC_BUILTIN	=	src/builtins/builtins.c			\
				src/builtins/my_cd.c			\
				src/builtins/where.c			\
				src/builtins/which.c			\
				src/builtins/repeat.c

SRC_CMDS	=	src/commands/commands.c			\
				src/commands/executor.c			\
				src/commands/pipes.c			\
				src/commands/redirects.c		\
				src/commands/history.c

SRC_PARSER	=	src/parser/memory.c				\
				src/parser/parser.c				\
				src/parser/token.c				\
				src/parser/subshell.c			\
				src/parser/operator.c			\
				src/parser/backticks.c			\
				src/parser/variable.c			\
				src/parser/variable_expansion.c

SRC_UTILS	=	src/utils/environment.c			\
				src/utils/utils.c				\
				src/utils/usage.c				\
				src/utils/parser_utils.c		\
				src/utils/pipe_utils.c			\
				src/utils/my_str_to_word_array.c\
				src/utils/my_arraylen.c			\
				src/utils/read_file.c			\
				src/utils/operator_utils.c		\
				src/utils/redirect_parsing.c	\

SRC_BASH 	= 	src/bash/set.c 					\
				src/bash/init_shell.c 			\
				src/bash/builtin_bash.c			\
				src/bash/bash_env.c

SRC_GLOBBING =  src/globbing/globbing.c 		\
				src/globbing/globbing_utils.c	\
				src/globbing/globbing_check.c	\
				src/globbing/globbing_count.c	\
				src/globbing/globbing_fill.c	\

SRC_ALIAS = 	src/alias/alias.c				\
				src/alias/builtin_alias.c		\
				src/alias/create_alias_list.c	\

SRC			=	$(SRC_CORE)						\
				$(SRC_BUILTIN)					\
				$(SRC_CMDS)						\
				$(SRC_PARSER)					\
				$(SRC_UTILS)					\
				$(SRC_BASH)						\
				$(SRC_GLOBBING)					\
				$(SRC_ALIAS)

OBJ			=	$(SRC:.c=.o)					\
				$(SRC_MAIN:.c=.o)

CFLAGS		=   -Wall -Wextra -Werror -iquote include
RM			=	rm -f
CP			=	cp
CC			=	gcc

NAME		=	42sh

all:			$(NAME)

debug: 	CFLAGS += -g3 -fsanitize=address
debug: 	re

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)

re:				fclean all

.PHONY:			all clean fclean all debug
