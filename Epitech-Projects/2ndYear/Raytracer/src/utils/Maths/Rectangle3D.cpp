/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Rectangle3D.cpp
*/

#include "Rectangle3D.hpp"

RayTracer::Rectangle3D::Rectangle3D()
{
    this->origin = Math::Point3D(0, 0, -1);
    this->bottom_side = Math::Vector3D(1, 0, 0);
    this->left_side = Math::Vector3D(0, 1, 0);
}

Math::Point3D RayTracer::Rectangle3D::pointAt(double u, double v)
{
    Math::Point3D center = this->origin - this->bottom_side - this->left_side;

    return center + u * (2 * this->bottom_side) + v * (2 * this->left_side);
}
