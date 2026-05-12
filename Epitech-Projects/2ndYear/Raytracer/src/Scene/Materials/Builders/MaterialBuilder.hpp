/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** MaterialBuilder
*/

#pragma once
#include "Material.hpp"
#include <memory>

namespace RayTracer {
    class MaterialBuilder {
        public:
            MaterialBuilder() = default;
            virtual ~MaterialBuilder() = default;
            MaterialBuilder &setColor(RayTracer::Color color){
                _material.setColor(color);
                return *this;
            };
            MaterialBuilder &setReflectivity(double reflectivity){
                _material.setReflectivity(reflectivity);
                return *this;
            };
            MaterialBuilder &setRefractivity(double refractivity){
                _material.setRefractivity(refractivity);
                return *this;
            };
            MaterialBuilder &setTransparency(double transparency){
                _material.setTransparency(transparency);
                return *this;
            };
            std::unique_ptr<RayTracer::Material> build() {
                return std::make_unique<RayTracer::Material>(_material);
            };
        protected:
            RayTracer::Color _color;
            Material _material;
    };
}
