##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/main.cpp \
		src/Core/Core.cpp \
		src/Core/Parser.cpp \
		src/Display/Display.cpp \
		src/Display/FileHandler.cpp \
		src/Scene/Camera/Camera.cpp \
		src/Scene/Camera/CameraBuilder.cpp \
		src/Scene/Lights/ALight.cpp \
		src/Scene/Lights/TypeLight/DirectionalLight.cpp \
		src/Scene/Lights/TypeLight/PointLight.cpp \
		src/Scene/Lights/Builder/DirectionalBuilder.cpp \
		src/Scene/Lights/Builder/PointBuilder.cpp \
		src/Scene/Materials/Material.cpp \
		src/Scene/Primitives/APrimitive.cpp \
		src/Scene/Primitives/Shapes/Plane.cpp \
		src/Scene/Primitives/Shapes/Sphere.cpp \
		src/Scene/Primitives/Shapes/Cone.cpp \
		src/Scene/Primitives/Shapes/Cylinder.cpp \
		src/utils/Color.cpp \
		src/utils/Maths/Vector3D.cpp \
		src/utils/Maths/Point3D.cpp \
		src/utils/Maths/Ray.cpp \
		src/utils/Maths/Rectangle3D.cpp \
		src/utils/Maths/Matrix4x4.cpp

NAME = raytracer

NAME_DEBUG = debug.raytracer

OBJ = $(SRC:.cpp=.o)

CFLAGS = -I.\
		-I./src\
		-I./src/Core\
		-I./src/Display\
		-I./src/Scene/Camera\
		-I./src/Scene/Lights\
		-I./src/Scene/Lights/TypeLight\
		-I./src/Scene/Lights/Builder\
		-I./src/Scene/Materials\
		-I./src/Scene/Materials/Builders\
		-I./src/Scene/Primitives\
		-I./src/Scene/Primitives/Builders\
		-I./src/Scene/Primitives/Shapes\
		-I./src/utils\
		-I./src/utils/Maths\

WARNINGS = -Wextra -Wall -Werror -std=c++20

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS) $(WARNINGS)

$(NAME): $(OBJ)
	clang++ $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME) $(LIBS)

$(NAME_DEBUG): $(OBJ)
	clang++ -g $(CFLAGS) $(WARNINGS) $(OBJ) -o $(NAME_DEBUG) $(LIBS)

all:	$(NAME)

debug:	$(NAME_DEBUG)
	valgrind ./$(NAME_DEBUG)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME) $(NAME_DEBUG)

re:	fclean all

.PHONY: debug clean fclean re
