/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** DirectionalLight.hpp
*/

#pragma once

#include "ALight.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

namespace RayTracer {
    class DirectionalLight : public RayTracer::ALight
    {
    private:
    public:
        DirectionalLight(Math::Vector3D direction, RayTracer::Color color, double ambientCoeff, double diffuseCoeff, double lightIntensity);
        ~DirectionalLight() = default;

        Math::Vector3D getLightDirection(Math::Point3D hitPoint) override;

        Math::Vector3D direction;
    };    
}