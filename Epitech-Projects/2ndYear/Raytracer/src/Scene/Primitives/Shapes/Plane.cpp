/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

RayTracer::Plane::Plane()
{
    this->_t = 0;
    this->axis = "Y";
    this->position = 2;
    this->_normal = Math::Vector3D(0, -1, 0);
}

RayTracer::Plane::Plane(std::string axis, double position, std::unique_ptr<RayTracer::Material> material)
{
    this->_t = 0;
    this->axis = axis;
    this->position = position;
    this->material = std::move(material);

    if (axis == "X")
        this->_normal = Math::Vector3D(1, 0, 0);
    else if (axis == "Y")
        this->_normal = Math::Vector3D(0, -1, 0);
    else if (axis == "Z")
        this->_normal = Math::Vector3D(0, 0, 1);
    else
        this->_normal = Math::Vector3D(1, 1, 1);
    
    this->_normal.normalize();
}

// Résolution d'équation :
// t = (pos - Oaxis) / Daxis

// pos = position du plane
// axis = "X", "Y" ou "Z"
// Oaxis = point "axis" de l'origin du rayon (ex: si axis est "X" -> Ox -> donc pour une origin (1, 2, 3) Ox est 1)
// Daxis = point "axis" de la direction du ray

bool RayTracer::Plane::hits(const RayTracer::Ray& ray, double& t)
{
    double Oaxis = (this->axis == "X") ? ray.origin.x : (this->axis == "Y") ? ray.origin.y : ray.origin.z;
    double Daxis = (this->axis == "X") ? ray.direction.x : (this->axis == "Y") ? ray.direction.y : ray.direction.z;
    double ecart = 0.000001;

    if (std::abs(Daxis) < ecart)
        return false;

    t = (this->position - Oaxis) / Daxis;

    if (t < ecart)
        return false;

    return true;
}

Math::Vector3D RayTracer::Plane::getNormal(const Math::Point3D& hitPoint) const
{
    (void)hitPoint;
    return this->_normal;
}
