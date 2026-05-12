/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Ray.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Ray
    {
    private:
        /* data */
    public:
        Ray() = default;
        Ray(Math::Point3D origin, Math::Vector3D direction);
        ~Ray() = default;

        Math::Point3D origin;
        Math::Vector3D direction;
    };    
}
