/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Color.hpp
*/

#pragma once

#include <iostream>

namespace RayTracer {
    class Color
    {
    public:
        Color() : r(0), g(0), b(0) {};
        Color(std::size_t r, std::size_t g, std::size_t b) : r(r), g(g), b(b) {};
        ~Color() = default;

        RayTracer::Color& operator=(const RayTracer::Color& c) = default;

        std::size_t r;
        std::size_t g;
        std::size_t b;
    };
}

RayTracer::Color operator+(const RayTracer::Color& c, double n);
RayTracer::Color operator*(const RayTracer::Color& c, double n);

RayTracer::Color operator+(const RayTracer::Color& c1, const RayTracer::Color& c2);
RayTracer::Color operator*(const RayTracer::Color& c1, const RayTracer::Color& c2);
std::ostream& operator<<(std::ostream &os, RayTracer::Color& c);