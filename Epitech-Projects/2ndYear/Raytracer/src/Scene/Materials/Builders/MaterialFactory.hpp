/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** MaterialFactory
*/

#pragma once
#include <memory>
#include <map>
#include <functional>
#include "MetalBuilder.hpp"

namespace RayTracer {
    class MaterialFactory {
        public:
            MaterialFactory() = default;
            ~MaterialFactory() = default;
            RayTracer::MaterialBuilder &create(const std::string &type) {
                auto it = _materialBuilders.find(type);
                if (it != _materialBuilders.end())
                    return it->second();
                return _materialBuilders.begin()->second();
            };
        private:
            inline const static std::map<std::string, std::function<RayTracer::MaterialBuilder&()>> _materialBuilders = {
                {"", []() -> RayTracer::MaterialBuilder & { static RayTracer::MaterialBuilder builder; return builder; }},
                {"metal", []() -> RayTracer::MaterialBuilder & { static RayTracer::MetalBuilder builder; return builder; }},
            };
    };
}