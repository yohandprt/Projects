/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Material
*/

#include "Material.hpp"

RayTracer::Material::Material()
: _color(0, 0, 0), _reflectivity(0.0), _refractivity(0.0), _transparency(0.0)
{
}

RayTracer::Material::Material(RayTracer::Color color)
: _color(color), _reflectivity(0.0), _refractivity(0.0), _transparency(0.0)
{
}

RayTracer::Material::Material(RayTracer::Color color, double reflectivity, double refractivity, double transparency)
: _color(color), _reflectivity(reflectivity), _refractivity(refractivity), _transparency(transparency)
{
}
