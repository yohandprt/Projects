/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** main.cpp
*/

#include "Core.hpp"
#include <iostream>

int main(int ac, const char** av)
{
    RayTracer::Core core;

    core.init(ac, av);

    try {
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}