/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** ALight.cpp
*/

#include "ALight.hpp"

double RayTracer::ALight::calculateLambert(Math::Vector3D normal, Math::Vector3D lightDirection)
{
    RayTracer::Color color;
    normal.normalize();
    lightDirection.normalize();

    return dot(normal, lightDirection);
}