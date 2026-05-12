/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Vector3D.cpp
*/

#include "Vector3D.hpp"
#include "Point3D.hpp"

Math::Vector3D::Vector3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Math::Vector3D::Vector3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Math::Vector3D::length()
{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double Math::Vector3D::dot(const Math::Vector3D& v)
{
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

void Math::Vector3D::normalize()
{
    double len = this->length();

    if (len == 0)
        return;
    
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

Math::Vector3D& Math::Vector3D::operator=(const Math::Point3D& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator+=(const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator-=(const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator*=(const Vector3D& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator/=(const Vector3D& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Math::Vector3D operator+(Math::Vector3D v1, const Math::Vector3D& v2)
{
    v1 += v2;
    return v1;
}

Math::Vector3D operator-(Math::Vector3D v1, const Math::Vector3D& v2)
{
    v1 -= v2;
    return v1;
}

Math::Vector3D operator*(Math::Vector3D v1, const Math::Vector3D& v2)
{
    v1 *= v2;
    return v1;
}

Math::Vector3D operator/(Math::Vector3D v1, const Math::Vector3D& v2)
{
    v1 /= v2;
    return v1;
}

Math::Vector3D operator*(double n, Math::Vector3D v)
{
    v.x *= n;
    v.y *= n;
    v.z *= n;
    return v;
}

std::ostream& operator<<(std::ostream &os, const Math::Vector3D& v)
{
    os << "(";
    os << v.x;
    os << ", ";
    os << v.y;
    os << ", ";
    os << v.z;
    os << ")";

    return os;
}

double dot(const Math::Vector3D& v1, const Math::Vector3D& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

double dot(const Math::Vector3D& v, const Math::Point3D& p)
{
    return (v.x * p.x) + (v.y * p.y) + (v.z * p.z);
}

double distance(const Math::Point3D& p1, const Math::Point3D& p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}
