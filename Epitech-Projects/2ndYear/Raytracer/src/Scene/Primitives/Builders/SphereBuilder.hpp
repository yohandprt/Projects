/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** SphereBuilder
*/

#pragma once
#include "Sphere.hpp"
#include "APrimBuilder.hpp"

namespace RayTracer {
    class SphereBuilder : public APrimBuilder<SphereBuilder> {
        public:
            SphereBuilder() = default;
            ~SphereBuilder() = default;

            SphereBuilder &setRadius(double radius) {_radius = radius; return *this;};
            std::unique_ptr<RayTracer::IPrimitive> build(){
                return std::make_unique<RayTracer::Sphere>(
                    Math::Point3D(_origin.x, _origin.y, _origin.z),
                    _radius, std::move(_material));
            }
        private:
            double _radius;
    };
}