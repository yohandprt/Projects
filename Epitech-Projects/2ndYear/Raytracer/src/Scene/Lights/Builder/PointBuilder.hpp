/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** PointBuilder.hpp
*/

#pragma once
#include <memory>
#include "PointLight.hpp"
#include "Point3D.hpp"
#include "Color.hpp"
#include "ALightBuilder.hpp"

namespace RayTracer {
    class PointBuilder : public ALightBuilder<PointBuilder>
    {
    private:
        Math::Point3D _origin;
    public:
        PointBuilder() = default;
        ~PointBuilder() = default;
        PointBuilder &setOrigin(double x = 0, double y = 0, double z = 0);
        PointBuilder &setColor(std::size_t r = 255, std::size_t g = 255, std::size_t b = 255);
        PointBuilder &setAmbient(double ambient)
            {_ambient = ambient; return *this;};
        PointBuilder &setDiffuse(double diffuse)
            {_diffuse = diffuse; return *this;};
        PointBuilder &setIntensity(double intensity)
            {_intensity = intensity; return *this;};
        std::unique_ptr<PointLight> build ()
            {return std::make_unique<PointLight>(_origin, _color, _ambient, _diffuse, _intensity);};
    };    
}