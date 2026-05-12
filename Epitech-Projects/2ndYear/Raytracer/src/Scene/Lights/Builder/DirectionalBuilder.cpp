/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** DirectionalBuilder.cpp
*/

#include "DirectionalBuilder.hpp"

RayTracer::DirectionalBuilder &RayTracer::DirectionalBuilder::setDirection(double x, double y, double z)
{
    _direction.x = x;
    _direction.y = y;
    _direction.z = z;
    return *this;
}

RayTracer::DirectionalBuilder &RayTracer::DirectionalBuilder::setColor(std::size_t r, std::size_t g, std::size_t b)
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
    return *this;
}