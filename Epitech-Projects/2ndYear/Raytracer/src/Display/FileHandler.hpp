/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** FileHandler.hpp
*/

#pragma once

#include <fstream>
#include <iostream>
#include <format>
#include "Color.hpp"

namespace RayTracer {
    class FileHandler
    {
    private:
        std::ofstream _file;
        std::string _filePath;
        double _width;
        double _height;

    public:
        FileHandler(std::string const &filePath);
        ~FileHandler();
        void init(double width, double height);

        void writeColor(RayTracer::Color color);
    };
}