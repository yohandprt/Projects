/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** APrimBuilder
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include <memory>

namespace RayTracer {
    template<typename Derived>
    class APrimBuilder
    {
        public:
            APrimBuilder() = default;
            ~APrimBuilder() = default;
            Derived &setOrigin(Math::Vector3D origin) {_origin = origin; return static_cast<Derived&>(*this);};
            Derived &setRotation(Math::Vector3D rotation) {_rotation = rotation; return static_cast<Derived&>(*this);};
            Derived &setScale(Math::Vector3D scale) {_scale = scale; return static_cast<Derived&>(*this);};
            Derived &setMaterial(std::unique_ptr<RayTracer::Material> material) {
                _material = std::move(material);
                return static_cast<Derived&>(*this);
            };

        protected:
            Math::Vector3D _origin;
            Math::Vector3D _rotation; 
            Math::Vector3D _scale;
            std::unique_ptr<RayTracer::Material> _material;
    };
}
