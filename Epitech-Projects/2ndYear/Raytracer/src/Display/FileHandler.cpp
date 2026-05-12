/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** FileHandler.cpp
*/

#include "FileHandler.hpp"

RayTracer::FileHandler::FileHandler(std::string const &filePath)
    :  _file(filePath), _filePath(filePath)
{
}

RayTracer::FileHandler::~FileHandler()
{
    this->_file.close();
}

void RayTracer::FileHandler::init(double width, double height)
{
    if (!this->_file.is_open()) {
        std::cerr << "Error: Could not open file " << this->_filePath << std::endl;
        return;
    }
    this->_width = width;
    this->_height = height;
    this->_file << "P3" << std::endl;
    this->_file << this->_width << " " << this->_height << std::endl;
    this->_file << "255" << std::endl;
}

void RayTracer::FileHandler::writeColor(RayTracer::Color color)
{
    std::string line = std::format("{} {} {}", color.r, color.g, color.b);
    this->_file << line << std::endl;
}
