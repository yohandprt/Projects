/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Cone.hpp
*/

#pragma once

#include "APrimitive.hpp"
#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Matrix4x4.hpp"

namespace RayTracer {
    class Cone : public APrimitive {
    private:
        Math::Point3D _center;
        double _radius;
        double _height;
        Math::Matrix4x4 _rot;
        Math::Matrix4x4 _invRot;
        mutable Math::Vector3D _localNormal;

    public:
        Cone(Math::Point3D center, double radius, double height,
             double rx, double ry, double rz,
             std::unique_ptr<RayTracer::Material> material);
        ~Cone() = default;

        bool hits(const RayTracer::Ray& ray, double& t) override;
        Math::Vector3D getNormal(const Math::Point3D& hitPoint) const override;
    };
}
