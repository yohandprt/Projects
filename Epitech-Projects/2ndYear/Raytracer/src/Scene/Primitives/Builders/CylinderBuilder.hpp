/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** CylinderBuilder.hpp
*/

#pragma once
#include "Cylinder.hpp"
#include "APrimBuilder.hpp"

namespace RayTracer {
    class CylinderBuilder : public APrimBuilder<CylinderBuilder> {
    public:
        CylinderBuilder() = default;
        ~CylinderBuilder() = default;

        CylinderBuilder &setRadius(double radius) { _radius = radius; return *this; }
        CylinderBuilder &setHeight(double height) { _height = height; return *this; }

        std::unique_ptr<RayTracer::IPrimitive> build() {
            return std::make_unique<RayTracer::Cylinder>(
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
