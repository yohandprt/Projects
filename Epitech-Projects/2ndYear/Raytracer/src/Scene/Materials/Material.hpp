/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Material
*/

#pragma once
#include "Color.hpp"

namespace RayTracer {
    class Material {
        private:
            Color _color;
            double _reflectivity;
            double _refractivity;
            double _transparency;
        public:
            Material();
            Material(RayTracer::Color color);
            Material(RayTracer::Color color, double reflectivity, double refractivity, double transparency);
            ~Material() = default;

            Color getColor() const {return _color;};
            double getReflectivity() const {return _reflectivity;};
            double getRefractivity() const {return _refractivity;};
            double getTransparency() const {return _transparency;};

            void setColor(RayTracer::Color color) {_color = color;};
            void setReflectivity(double reflectivity) {_reflectivity = reflectivity;};
            void setRefractivity(double refractivity) {_refractivity = refractivity;};
            void setTransparency(double transparency) {_transparency = transparency;};
    };
}
