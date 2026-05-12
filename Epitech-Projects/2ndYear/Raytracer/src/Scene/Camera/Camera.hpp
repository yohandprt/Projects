/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Camera.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Rectangle3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"


namespace RayTracer {
    class Camera
    {
    private:
        /* data */
    public:
        Camera();
        ~Camera() = default;

        RayTracer::Ray ray(double x, double y);

        Math::Point3D origin;
        RayTracer::Rectangle3D screen;
        double resolutionX;
        double resolutionY;
        RayTracer::Color bgColor;
        double fov;
    };    
}