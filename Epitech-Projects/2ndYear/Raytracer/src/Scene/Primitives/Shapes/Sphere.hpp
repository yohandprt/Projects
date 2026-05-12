/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Sphere.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "APrimitive.hpp"
#include "ALight.hpp"

#include <tuple>

namespace RayTracer {
    class Sphere : public RayTracer::APrimitive
    {
    private:
    public:
        Sphere();
        Sphere(Math::Point3D center, double radius, std::unique_ptr<RayTracer::Material> material);
        ~Sphere() = default;

        bool hits(const RayTracer::Ray& ray, double& t) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;

        Math::Point3D center;
        double radius;
    };
}
