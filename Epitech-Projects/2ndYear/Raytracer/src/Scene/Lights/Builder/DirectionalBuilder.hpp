/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** DirectionalBuilder.hpp
*/

#pragma once
#include "DirectionalLight.hpp"
#include "ALightBuilder.hpp"

namespace RayTracer {
    class DirectionalBuilder : public RayTracer::ALightBuilder<DirectionalBuilder>
    {
    private:
        Math::Vector3D _direction;
    public:
        DirectionalBuilder() = default;
        ~DirectionalBuilder() = default;
        DirectionalBuilder &setDirection(double x = 0, double y = 0, double z = -1);
        DirectionalBuilder &setColor(std::size_t r = 255, std::size_t g = 255, std::size_t b = 255);
        DirectionalBuilder &setAmbient(double ambient)
            {_ambient = ambient; return *this;};
        DirectionalBuilder &setDiffuse(double diffuse)
            {_diffuse = diffuse; return *this;};
        DirectionalBuilder &setIntensity(double intensity)
            {_intensity = intensity; return *this;};
        std::unique_ptr<DirectionalLight> build ()
            {return std::make_unique<DirectionalLight>(_direction, _color, _ambient, _diffuse, _intensity);};
    };    
}