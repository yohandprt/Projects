/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Matrix4x4.hpp
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cmath>

namespace Math {
    class Matrix4x4 {
    private:
        double m[4][4];

    public:
        Matrix4x4();
        ~Matrix4x4() = default;

        static Matrix4x4 translation(double x, double y, double z);
        static Matrix4x4 rotation_x(double angle_degrees);
        static Matrix4x4 rotation_y(double angle_degrees);
        static Matrix4x4 rotation_z(double angle_degrees);
        Matrix4x4 transpose() const;

        Point3D operator*(const Point3D& p) const;
        Vector3D operator*(const Vector3D& v) const;
        Matrix4x4 operator*(const Matrix4x4& other) const;

        double get(int row, int col) const;
        void set(int row, int col, double value);
    };
}
