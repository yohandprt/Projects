/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Matrix4x4.cpp
*/

#include "Matrix4x4.hpp"

Math::Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

Math::Matrix4x4 Math::Matrix4x4::translation(double x, double y, double z)
{
    Matrix4x4 result;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

Math::Matrix4x4 Math::Matrix4x4::rotation_x(double angle_degrees)
{
    Matrix4x4 result;
    double angle_rad = angle_degrees * M_PI / 180.0;
    double c = std::cos(angle_rad);
    double s = std::sin(angle_rad);

    result.m[1][1] =  c;
    result.m[1][2] = -s;
    result.m[2][1] =  s;
    result.m[2][2] =  c;

    return result;
}

Math::Matrix4x4 Math::Matrix4x4::rotation_y(double angle_degrees)
{
    Matrix4x4 result;
    double angle_rad = angle_degrees * M_PI / 180.0;
    double c = std::cos(angle_rad);
    double s = std::sin(angle_rad);

    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;

    return result;
}

Math::Matrix4x4 Math::Matrix4x4::rotation_z(double angle_degrees)
{
    Matrix4x4 result;
    double angle_rad = angle_degrees * M_PI / 180.0;
    double c = std::cos(angle_rad);
    double s = std::sin(angle_rad);

    result.m[0][0] =  c;
    result.m[0][1] = -s;
    result.m[1][0] =  s;
    result.m[1][1] =  c;
    return result;
}

Math::Matrix4x4 Math::Matrix4x4::transpose() const
{
    Matrix4x4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m[j][i];
    return result;
}

Math::Point3D Math::Matrix4x4::operator*(const Point3D& p) const
{
    double x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + m[0][3];
    double y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + m[1][3];
    double z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + m[2][3];
    return Point3D(x, y, z);
}

Math::Vector3D Math::Matrix4x4::operator*(const Vector3D& v) const
{
    double x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2];
    double y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2];
    double z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2];
    return Vector3D(x, y, z);
}

Math::Matrix4x4 Math::Matrix4x4::operator*(const Matrix4x4& other) const
{
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

double Math::Matrix4x4::get(int row, int col) const
{
    return m[row][col];
}

void Math::Matrix4x4::set(int row, int col, double value)
{
    m[row][col] = value;
}
