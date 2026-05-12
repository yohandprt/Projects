/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Color.cpp
*/

#include "Color.hpp"

// RayTracer::Color& RayTracer::Color::operator=(const RayTracer::Color& c)
// {
//     this->r = c.r;
//     this->g = c.g;
//     this->b = c.b;

//     return *this;
// }

RayTracer::Color operator+(const RayTracer::Color& c, double n)
{
    RayTracer::Color color;

    color.r = c.r + n;
    color.g = c.g + n;
    color.b = c.b + n;

    return color;
}

RayTracer::Color operator*(const RayTracer::Color& c, double n)
{
    RayTracer::Color color;

    color.r = c.r * n;
    color.g = c.g * n;
    color.b = c.b * n;

    return color;
}

RayTracer::Color operator+(const RayTracer::Color& c1, const RayTracer::Color& c2)
{
    RayTracer::Color color;

    color.r = c1.r + c2.r;
    color.g = c1.g + c2.g;
    color.b = c1.b + c2.b;

    return color;
}

RayTracer::Color operator*(const RayTracer::Color& c1, const RayTracer::Color& c2)
{
    RayTracer::Color color;

    color.r = c1.r * c2.r;
    color.g = c1.g * c2.g;
    color.b = c1.b * c2.b;

    return color;
}

std::ostream& operator<<(std::ostream &os, RayTracer::Color& c)
{
    os << "(";
    os << c.r;
    os << ", ";
    os << c.g;
    os << ", ";
    os << c.b;
    os << ")";

    return os;
}