/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** ALight.hpp
*/

#pragma once

#include "ILight.hpp"
#include "Color.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class ALight : public RayTracer::ILight
    {
    protected:
        double _ambientCoeff;
        double _diffuseCoeff;
        double _lightIntensity;
        double _currentDiffuse;
    public:
        ALight() = default;
        ~ALight() = default;

        double calculateLambert(Math::Vector3D normal, Math::Vector3D lightDirection) override;
        Math::Vector3D getLightDirection(Math::Point3D hitPoint) override {return (origin - hitPoint).toVector();};
        double getAmbientCoeff() override {return _ambientCoeff;};
        double getDiffuseCoeff() override {return _diffuseCoeff;};
        double getLightIntensity() override {return _lightIntensity;};
        double getCurrentDiffuse() override {return _currentDiffuse;};
        RayTracer::Color getColor() const override {return color;};

        RayTracer::Color color;
        Math::Point3D origin;
    };
}