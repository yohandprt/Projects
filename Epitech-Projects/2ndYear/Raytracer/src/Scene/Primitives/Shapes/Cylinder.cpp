/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"
#include <cmath>

RayTracer::Cylinder::Cylinder(Math::Point3D center, double radius, double height,
                               double rx, double ry, double rz,
                               std::unique_ptr<RayTracer::Material> material)
    : _center(center), _radius(radius), _height(height)
{
    this->material = std::move(material);
    _rot    = Math::Matrix4x4::rotation_z(rz) *
              Math::Matrix4x4::rotation_y(ry) *
              Math::Matrix4x4::rotation_x(rx);
    _invRot = _rot.transpose();
}

bool RayTracer::Cylinder::hits(const RayTracer::Ray& ray, double& t)
{
    Math::Vector3D oc = _invRot * (ray.origin - _center).toVector();
    Math::Vector3D d  = _invRot * ray.direction;

    double half   = _height / 2.0;
    double t_best = -1;
    Math::Vector3D N_best;

    double a = d.x * d.x + d.z * d.z;
    if (a >= 1e-9) {
        double b = 2.0 * (oc.x * d.x + oc.z * d.z);
        double c = oc.x * oc.x + oc.z * oc.z - _radius * _radius;
        double delta = b * b - 4.0 * a * c;

        if (delta >= 0) {
            double sq = std::sqrt(delta);
            double ts[2] = {(-b - sq) / (2.0 * a), (-b + sq) / (2.0 * a)};
            for (double ti : ts) {
                if (ti < 1e-9) continue;
                double y = oc.y + ti * d.y;
                if (y < -half || y > half) continue;
                if (t_best < 0 || ti < t_best) {
                    Math::Vector3D hp(oc.x + ti*d.x, oc.y + ti*d.y, oc.z + ti*d.z);
                    t_best = ti;
                    N_best = Math::Vector3D(hp.x, 0, hp.z);
                }
                break;
            }
        }
    }
    if (std::abs(d.y) > 1e-9) {
        double tb = (-half - oc.y) / d.y;
        if (tb >= 1e-9 && (t_best < 0 || tb < t_best)) {
            double px = oc.x + tb * d.x;
            double pz = oc.z + tb * d.z;
            if (px*px + pz*pz <= _radius * _radius) {
                t_best = tb;
                N_best = Math::Vector3D(0, -1, 0);
            }
        }
        double tt = (half - oc.y) / d.y;
        if (tt >= 1e-9 && (t_best < 0 || tt < t_best)) {
            double px = oc.x + tt * d.x;
            double pz = oc.z + tt * d.z;
            if (px*px + pz*pz <= _radius * _radius) {
                t_best = tt;
                N_best = Math::Vector3D(0, 1, 0);
            }
        }
    }
    if (t_best < 0)
        return false;
    t = t_best;
    _localNormal = N_best;
    return true;
}

Math::Vector3D RayTracer::Cylinder::getNormal(const Math::Point3D& hitPoint) const
{
    (void)hitPoint;
    Math::Vector3D n = _rot * _localNormal;
    n.normalize();
    return n;
}
