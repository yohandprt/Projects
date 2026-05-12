/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** PointLight.hpp
*/

#pragma once

#include "ALight.hpp"

namespace RayTracer {
    class PointLight : public RayTracer::ALight
    {
    private:
    public:
        PointLight(Math::Point3D origin, RayTracer::Color color, double ambientCoeff, double diffuseCoeff, double lightIntensity);
        ~PointLight() = default;
    };
}