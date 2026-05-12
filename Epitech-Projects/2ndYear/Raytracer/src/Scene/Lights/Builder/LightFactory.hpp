/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-raytracer-12
** File description:
** LightFactory.hpp
*/

#pragma once
#include <memory>
#include <map>
#include <functional>
#include "PointBuilder.hpp"
#include "DirectionalBuilder.hpp"

namespace RayTracer {
    class LightFactory {
        public:
            LightFactory() = default;
            ~LightFactory() = default;

            RayTracer::/* lightbuilder */ &create(const std::string &type) {
                auto it = _lightBuilders.find(type);
                if (it != _lightBuilders.end())
                    return it->second();
                return _lightBuilders.begin()->second();
            };

        private:
            inline const static std::map<std::string, std::function<RayTracer::/* lightbuilder */&()>> _lightBuilders = {
                {"point",       []() -> RayTracer:: /* lightbuilder */ & { static RayTracer::PointBuilder builder;       return builder; }},
                {"directional", []() -> RayTracer:: /* lightbuilder */ & { static RayTracer::DirectionalBuilder builder; return builder; }},
            };
    };
}