/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"

RayTracer::DirectionalLight::DirectionalLight(Math::Vector3D direction, RayTracer::Color color, double ambientCoeff, double diffuseCoeff, double lightIntensity)
{
    this->direction = direction;
    this->direction.normalize();
    this->color = color;
    this->_ambientCoeff = ambientCoeff;
    this->_diffuseCoeff = diffuseCoeff;
    this->_lightIntensity = lightIntensity;
}

Math::Vector3D RayTracer::DirectionalLight::getLightDirection(Math::Point3D hitPoint)
{
    (void)hitPoint;
    return -1 * this->direction;
}
