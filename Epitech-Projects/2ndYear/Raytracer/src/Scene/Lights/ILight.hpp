/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** ILight.hpp
*/

#pragma once

#include "Color.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class ILight
    {
    public:
        virtual ~ILight() = default;

        virtual double calculateLambert(Math::Vector3D normal, Math::Vector3D lightDirection) = 0;
        virtual Math::Vector3D getLightDirection(Math::Point3D hitPoint) = 0;
        virtual double getAmbientCoeff() = 0;
        virtual double getDiffuseCoeff() = 0;
        virtual double getLightIntensity() = 0;
        virtual double getCurrentDiffuse() = 0;
        virtual RayTracer::Color getColor() const = 0;
    };
}