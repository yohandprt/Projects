/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** IPrimitive.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "ALight.hpp"
#include "Material.hpp"

#include <vector>
#include <memory>

namespace RayTracer {
    class IPrimitive
    {
    public:
        virtual ~IPrimitive() = default;

        virtual bool hits(const RayTracer::Ray& ray, double& t) = 0;
        virtual Math::Point3D getHitPoint() = 0;
        virtual Math::Vector3D getNormal(const Math::Point3D& hitPoint) const = 0;
        virtual RayTracer::Color getColor() const = 0;
        virtual std::unique_ptr<RayTracer::Material>& getMaterial() = 0;
        virtual RayTracer::Color calculatePixelColor(const Math::Point3D& hitPoint, const RayTracer::Ray& r, const std::vector<std::unique_ptr<RayTracer::ILight>>& lights, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives) = 0;
        virtual bool isInShadow(const Math::Point3D& hitPoint, const Math::Vector3D& L, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives) = 0;
    };
}
