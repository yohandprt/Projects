/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"

RayTracer::Sphere::Sphere()
{
    this->radius = 0;
}

RayTracer::Sphere::Sphere(Math::Point3D center, double radius, std::unique_ptr<RayTracer::Material> material)
{
    this->center = center;
    this->radius = radius;
    this->material = std::move(material);
}

// Résolution d'équation :
// delta = b2 - 4ac

// a = D.D
// b = 2(D.L)
// c = L.L - r2

// D = direction du ray
// O = origin du ray
// C = centre de la sphere
// L = O - C
// R = rayon de la sphere
// R2 = R * R

bool RayTracer::Sphere::hits(const RayTracer::Ray& ray, double& t)
{
    Math::Vector3D L = (ray.origin - this->center).toVector();

    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(ray.direction, L);
    double c = dot(L, L) - (this->radius * this->radius);

    double delta = b * b - 4 * a * c;

    if (delta < 0.0)
        return false;

    double ecart = 0.0001;
    double sqrtDelta = std::sqrt(delta);
    double t1 = (-b - sqrtDelta) / (2.0 * a);
    double t2 = (-b + sqrtDelta) / (2.0 * a);

    if (t1 > ecart)
        t = t1;
    else if (t2 > ecart)
        t = t2;
    else
        return false;
    return true;
}

Math::Vector3D RayTracer::Sphere::getNormal(const Math::Point3D& hitPoint) const
{
    return (hitPoint - this->center).toVector();
}
