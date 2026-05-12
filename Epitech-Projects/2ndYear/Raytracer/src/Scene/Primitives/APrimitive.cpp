/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** APrimitive.cpp
*/

#include "APrimitive.hpp"

RayTracer::Color RayTracer::APrimitive::getColor() const
{
    return this->material->getColor();
}

std::unique_ptr<RayTracer::Material>& RayTracer::APrimitive::getMaterial()
{
    return this->material;
}

RayTracer::Color RayTracer::APrimitive::calculatePixelColor(const Math::Point3D& hitPoint, const RayTracer::Ray& r, const std::vector<std::unique_ptr<RayTracer::ILight>>& lights, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives)
{
    RayTracer::Color finalColor(0, 0, 0);

    Math::Vector3D N = this->getNormal(hitPoint);
    Math::Vector3D L;
    N.normalize();

    for (const auto& light : lights)
    {
        L = light->getLightDirection(hitPoint);
        L.normalize();

        finalColor = finalColor + this->getColor() * light->getAmbientCoeff();

        double lambert = std::max(0.0, dot(N, L));

        if (lambert <= 0.0)
            continue;

        if (isInShadow(hitPoint, L, primitives))
            continue;

        double diffuse = lambert * light->getDiffuseCoeff();
        diffuse *= (1.0 - this->material->getReflectivity());

        Math::Vector3D V = -1 * r.direction;
        Math::Vector3D R = (2.0 * lambert * N - L);
        V.normalize();
        R.normalize();

        double phong = std::pow(std::max(0.0, dot(R, V)), 50);

        finalColor = finalColor + this->getColor() * diffuse + light->getColor() * (phong * light->getLightIntensity());
    }

    return finalColor;
}

bool RayTracer::APrimitive::isInShadow(const Math::Point3D& hitPoint, const Math::Vector3D& L, const std::vector<std::unique_ptr<RayTracer::IPrimitive>>& primitives)
{
    RayTracer::Ray shadowRay;
    shadowRay.origin = hitPoint + 0.0001 * L;
    shadowRay.direction = L;

    for (const auto& primitive : primitives)
    {
        if (primitive.get() == this)
            continue;

        double t;
        if (primitive->hits(shadowRay, t) && t > 0.0001)
            return true;
    }

    return false;
}
