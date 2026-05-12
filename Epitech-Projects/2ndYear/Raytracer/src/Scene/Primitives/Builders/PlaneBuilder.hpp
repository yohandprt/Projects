/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** PlaneBuilder
*/

#pragma once
#include "Plane.hpp"
#include "APrimBuilder.hpp"

namespace RayTracer {
    class PlaneBuilder : public APrimBuilder<PlaneBuilder> {
        public:
            PlaneBuilder() = default;
            ~PlaneBuilder() = default;

            PlaneBuilder &setAxis(std::string axis) {_axis = axis; return *this;};
            PlaneBuilder &setPosition(double position) {_position = position; return *this;};
            std::unique_ptr<RayTracer::IPrimitive> build(){
                return std::make_unique<RayTracer::Plane>(_axis, _position, std::move(_material));
            }
        private:
            std::string _axis;
            double _position;
    };
}
