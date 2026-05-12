/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** ALightBuilder.hpp
*/

#pragma once

#include "ILight.hpp"

namespace RayTracer {
    template<typename Derived>
    class ALightBuilder
    {
    protected:
        Color _color;
        double _ambient;
        double _diffuse;
        double _intensity;
    public:
        ALightBuilder() = default;
        ~ALightBuilder() = default;
        Derived &setColor(std::size_t r = 255, std::size_t g = 255, std::size_t b = 255)
            {_color.r = r; _color.g = g; _color.b = b; return static_cast<Derived&>(*this);};
        Derived &setAmbient(double ambient = 0.3)
            {_ambient = ambient; return static_cast<Derived&>(*this);};
        Derived &setDiffuse(double diffuse = 0.8)
            {_diffuse = diffuse; return static_cast<Derived&>(*this);};
        Derived &setIntensity(double intensity = 1.0)
            {_intensity = intensity; return static_cast<Derived&>(*this);};
    };
}