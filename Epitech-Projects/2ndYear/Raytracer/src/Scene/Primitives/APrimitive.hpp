/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** APrimitive.hpp
*/

#pragma once

#include "IPrimitive.hpp"
#include "Material.hpp"
#include <memory>

namespace RayTracer {
    class APrimitive : public RayTracer::IPrimitive
    {
    protected:
    public:
        virtual ~APrimitive() = default;
        
        bool hits(const RayTracer::Ray& ray, double& t) override {
            (void)ray;
            (void)t;
            return false;
        };
        Math::Point3D getHitPoint() override {return hitPoint;};
        RayTracer::Color getColor() const override;
        std::unique_ptr<RayTracer::Material>& getMaterial() override;
        RayTracer::Color calculatePixelColor(const Math::Point3D& hitPoint, const RayTracer::Ray& r, const std::vector<std::unique_ptr<RayTracer::ILight>>& lights, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives) override;
        bool isInShadow(const Math::Point3D& hitPoint, const Math::Vector3D& L, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives) override;
        Math::Point3D hitPoint;
        Math::Point3D exitPoint;
        std::unique_ptr<RayTracer::Material> material;
    };
}
