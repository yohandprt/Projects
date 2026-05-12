/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** PointBuilder.cpp
*/

#include "PointBuilder.hpp"

RayTracer::PointBuilder &RayTracer::PointBuilder::setOrigin(double x, double y, double z)
{
    _origin.x = x;
    _origin.y = y;
    _origin.z = z;
    return *this;
}

RayTracer::PointBuilder &RayTracer::PointBuilder::setColor(std::size_t r, std::size_t g, std::size_t b)
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
    return *this;
}