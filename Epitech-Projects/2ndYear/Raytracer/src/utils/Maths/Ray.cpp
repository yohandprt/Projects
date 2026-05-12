/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

RayTracer::Ray::Ray(Math::Point3D origin, Math::Vector3D direction)
{
    this->origin = origin;
    this->direction = direction;
}