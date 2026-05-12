/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** CameraBuilder
*/

#pragma once
#include "Camera.hpp"
#include <memory>

namespace RayTracer {
    class CameraBuilder {
        public:
            CameraBuilder() = default;
            ~CameraBuilder() = default;
            CameraBuilder &setOrigin(double x = 0, double y = 0, double z = 0);
            CameraBuilder &setResolution(double resX = 1920, double resY = 1080);
            CameraBuilder &setFov(double fov = 90);
            CameraBuilder &setBgColor(std::size_t r = 0, std::size_t g = 0, std::size_t b = 0);
            std::unique_ptr<Camera> build(void) {
                double aspectRatio = cam.resolutionX / cam.resolutionY;
                if (aspectRatio >= 1.0) {
                    cam.screen.bottom_side = Math::Vector3D(aspectRatio, 0, 0);
                    cam.screen.left_side   = Math::Vector3D(0, 1, 0);
                } else {
                    cam.screen.bottom_side = Math::Vector3D(1, 0, 0);
                    cam.screen.left_side   = Math::Vector3D(0, 1.0 / aspectRatio, 0);
                }
                return std::make_unique<Camera>(cam);
            }
        private:
            Camera cam;
    };
}