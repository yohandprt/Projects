/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Point3D.hpp
*/

#pragma once

#include "Vector3D.hpp"

#include <iostream>

namespace Math {
    class Point3D
    {
    private:
        /* data */
    public:
        Point3D();
        Point3D(double x, double y, double z);
        ~Point3D() = default;

        Math::Vector3D toVector();

        Math::Point3D& operator+=(const Math::Vector3D& v);
        Math::Point3D& operator-=(const Math::Vector3D& v);

        double x;
        double y;
        double z;
    };
}

Math::Point3D operator+(Math::Point3D p, const Math::Vector3D& v);
Math::Point3D operator-(Math::Point3D p, const Math::Vector3D& v);
double operator*(const Math::Point3D& p, const Math::Vector3D& v);

Math::Point3D operator-(const Math::Point3D& p1, const Math::Point3D& p2);
double operator*(const Math::Point3D& p1, const Math::Point3D& p2);

std::ostream& operator<<(std::ostream &os, Math::Point3D& p);

double dot(const Math::Point3D& p1, const Math::Point3D& p2);
