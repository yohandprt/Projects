/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

RayTracer::PointLight::PointLight(Math::Point3D origin, RayTracer::Color color, double ambientCoeff, double diffuseCoeff, double lightIntensity)
{
    this->origin = origin;
    this->color = color;
    this->_ambientCoeff = ambientCoeff;
    this->_diffuseCoeff = diffuseCoeff;
    this->_lightIntensity = lightIntensity;
}
