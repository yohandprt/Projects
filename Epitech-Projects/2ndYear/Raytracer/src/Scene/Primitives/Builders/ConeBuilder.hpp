/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** ConeBuilder.hpp
*/

#pragma once
#include "Cone.hpp"
#include "APrimBuilder.hpp"

namespace RayTracer {
    class ConeBuilder : public APrimBuilder<ConeBuilder> {
    public:
        ConeBuilder() = default;
        ~ConeBuilder() = default;

        ConeBuilder &setRadius(double radius) { _radius = radius; return *this; }
        ConeBuilder &setHeight(double height) { _height = height; return *this; }

        std::unique_ptr<RayTracer::IPrimitive> build() {
            return std::make_unique<RayTracer::Cone>(
                Math::Point3D(_origin.x, _origin.y, _origin.z),
                _radius, _height,
                _rotation.x, _rotation.y, _rotation.z,
                std::move(_material)
            );
        }

    private:
        double _radius = 0;
        double _height = 1;
    };
}
