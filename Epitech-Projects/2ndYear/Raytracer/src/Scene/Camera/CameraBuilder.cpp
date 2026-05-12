/*
** EPITE, 2026
** RayTracer
** File description:
** CameraBuilder
*/

#include "CameraBuilder.hpp"

RayTracer::CameraBuilder &RayTracer::CameraBuilder::setOrigin(double x, double y, double z)
{
    cam.origin.x = x;
    cam.origin.y = y;
    cam.origin.z = z;
    return *this;
}
RayTracer::CameraBuilder &RayTracer::CameraBuilder::setResolution(double resX, double resY)
{
    cam.resolutionX = resX;
    cam.resolutionY = resY;
    return *this;
}
RayTracer::CameraBuilder &RayTracer::CameraBuilder::setFov(double fov)
{
    cam.fov = fov;
    return *this;
}
RayTracer::CameraBuilder &RayTracer::CameraBuilder::setBgColor(std::size_t r, std::size_t g, std::size_t b)
{
    cam.bgColor.r = r;
    cam.bgColor.g = g;
    cam.bgColor.b = b;
    return *this;
}