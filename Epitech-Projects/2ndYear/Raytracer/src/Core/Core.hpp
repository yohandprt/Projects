/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Core
*/

#pragma once

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Camera.hpp"
#include "Display.hpp"
#include "FileHandler.hpp"
#include "Color.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "Parser.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <memory>

#define MAX_NB_RAY 2

namespace RayTracer {
    class Core {
        public:
            Core();
            ~Core() = default;
            void init(const int ac, const char** av);
            RayTracer::Color getPixelColor(std::size_t x, std::size_t y);
            std::size_t getClosestPixel(const RayTracer::Ray& r, std::size_t idxCurrentPrim);
            RayTracer::Color traceRay(const Ray& r, std::size_t depth, std::size_t idxCurrentPrim);
            void run();
        private:
            std::unique_ptr<RayTracer::Display> _render;
            std::unique_ptr<RayTracer::Parser> _parser;
            std::unique_ptr<RayTracer::FileHandler> _fileHandler;
            std::unique_ptr<RayTracer::Camera> _camera;
            std::vector<std::unique_ptr<RayTracer::IPrimitive>> _primitives;
            std::vector<std::unique_ptr<RayTracer::ILight>> _lights;
            double _closestT;
        };
};