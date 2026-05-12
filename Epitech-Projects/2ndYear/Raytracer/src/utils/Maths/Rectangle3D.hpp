/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Rectangle3D.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Rectangle3D
    {
    private:
        /* data */
    public:
        Rectangle3D();
        ~Rectangle3D() = default;

        Math::Point3D pointAt(double u, double v);

        Math::Point3D origin;
        Math::Vector3D bottom_side;
        Math::Vector3D left_side;

    };
}