/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

RayTracer::Camera::Camera()
{
    this->origin = Math::Point3D(0, 0, 0);
}

RayTracer::Ray RayTracer::Camera::ray(double x, double y)
{
    RayTracer::Ray rayon;
    double u = x / (this->resolutionX - 1);
    double v = y / (this->resolutionY - 1);
    Math::Point3D pointOnScreen = this->screen.pointAt(u, v);

    rayon.origin = this->origin;
    rayon.direction = (pointOnScreen - rayon.origin);
    rayon.direction.normalize();

    return rayon;
}
