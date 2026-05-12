/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Plane.hpp
*/

#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "APrimitive.hpp"

namespace RayTracer {
    class Plane : public RayTracer::APrimitive
    {
    private:
        double _t;
        Math::Vector3D _normal;
    public:
        Plane();
        Plane(std::string axis, double position, std::unique_ptr<RayTracer::Material> material);
        ~Plane() = default;

        bool hits(const RayTracer::Ray& ray, double& t) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;

        std::string axis;
        double position;
    };
}
