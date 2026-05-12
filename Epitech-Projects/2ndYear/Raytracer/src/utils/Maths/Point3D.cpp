/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Point3D.cpp
*/

#include "Point3D.hpp"

Math::Point3D::Point3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Math::Point3D::Point3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Math::Vector3D Math::Point3D::toVector()
{
    Math::Vector3D newVector;

    newVector.x = this->x;
    newVector.y = this->y;
    newVector.z = this->z;

    return newVector;
}

Math::Point3D& Math::Point3D::operator+=(const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Math::Point3D& Math::Point3D::operator-=(const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Math::Point3D operator+(Math::Point3D p, const Math::Vector3D& v)
{
    p += v;
    return p;
}

Math::Point3D operator-(Math::Point3D p, const Math::Vector3D& v)
{
    p -= v;
    return p;
}

Math::Point3D operator-(const Math::Point3D& p1, const Math::Point3D& p2)
{
    return Math::Point3D(
        p1.x - p2.x,
        p1.y - p2.y,
        p1.z - p2.z
    );
}

double operator*(const Math::Point3D& p, const Math::Vector3D& v)
{
    return p.x*v.x + p.y*v.y + p.z*v.z;
}

double operator*(const Math::Point3D& p1, const Math::Point3D& p2)
{
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

std::ostream& operator<<(std::ostream &os, Math::Point3D& p)
{
    os << "(";
    os << p.x;
    os << ", ";
    os << p.y;
    os << ", ";
    os << p.z;
    os << ")";

    return os;
}

double dot(const Math::Point3D& p1, const Math::Point3D& p2)
{
    return (p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z);
}