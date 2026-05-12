/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Vector3D.hpp
*/

#pragma once

#include <cmath>
#include <iostream>

namespace Math {
    class Point3D;
    class Vector3D
    {
    private:
        /* data */
    public:
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D() = default;
        Vector3D(const Vector3D&) = default;
        Vector3D& operator=(const Vector3D&) = default;

        double length();
        double dot(const Math::Vector3D& v);

        void normalize();

        Math::Vector3D& operator+=(const Math::Vector3D& v);
        Math::Vector3D& operator-=(const Math::Vector3D& v);
        Math::Vector3D& operator*=(const Math::Vector3D& v);
        Math::Vector3D& operator/=(const Math::Vector3D& v);

        Math::Vector3D& operator=(const Math::Point3D& p);

        double x;
        double y;
        double z;
    };
}

Math::Vector3D operator+(Math::Vector3D v1, const Math::Vector3D& v2);
Math::Vector3D operator-(Math::Vector3D v1, const Math::Vector3D& v2);
Math::Vector3D operator*(Math::Vector3D v1, const Math::Vector3D& v2);
Math::Vector3D operator/(Math::Vector3D v1, const Math::Vector3D& v2);

Math::Vector3D operator*(double n, Math::Vector3D v);

std::ostream& operator<<(std::ostream &os, const Math::Vector3D& v);

double dot(const Math::Vector3D& v1, const Math::Vector3D& v2);
double dot(const Math::Vector3D& v, const Math::Point3D& p);

double distance(const Math::Point3D& p1, const Math::Point3D& p2);