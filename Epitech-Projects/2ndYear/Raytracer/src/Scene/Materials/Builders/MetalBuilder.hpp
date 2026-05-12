/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** MetalBuilder
*/

#pragma once
#include "MaterialBuilder.hpp"

namespace RayTracer {
    class MetalBuilder : public MaterialBuilder {
        public:
            MetalBuilder() {
                _material._reflectivity = 0.8;
                _material._refractivity = 0.0;
                _material._transparency = 0.0;
            };
            ~MetalBuilder() = default;
        private:
    };
}