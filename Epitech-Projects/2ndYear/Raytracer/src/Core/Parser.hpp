/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Parser
*/

#pragma once

#include "CameraBuilder.hpp"
#include "ALightBuilder.hpp"
#include "DirectionalBuilder.hpp"
#include "PointBuilder.hpp"
#include "MaterialBuilder.hpp"
#include "FileHandler.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "Material.hpp"
// TODO: add builder/light includes when implementing parseShapes and parseLights:
#include "SphereBuilder.hpp"
#include "PlaneBuilder.hpp"
#include "ConeBuilder.hpp"
#include "CylinderBuilder.hpp"
#include "MaterialBuilder.hpp"
#include <libconfig.h++>
#include <vector>
#include <memory>

namespace RayTracer {
    class Parser {
        public:
            class Error : public std::exception {
                public:
                    Error(const std::string &message) : _message(message) {}
                    const char* what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };
            Parser();
            ~Parser();
            int parse(const int ac, const char** av);
            std::unique_ptr<RayTracer::FileHandler>
                parseFileHandler();
            std::unique_ptr<RayTracer::Camera>
                parseCamera();
            std::vector<std::unique_ptr<RayTracer::ILight>>
                parseLights();
            std::unique_ptr<RayTracer::Material>
                parseMaterial(libconfig::Setting &s);
            std::vector<std::unique_ptr<RayTracer::IPrimitive>>
                parseShapes();
        private:
            std::string _filepath;
            libconfig::Config cfg;
    };
}
