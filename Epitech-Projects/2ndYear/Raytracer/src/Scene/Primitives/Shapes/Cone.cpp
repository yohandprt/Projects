/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"
#include <cmath>

RayTracer::Cone::Cone(Math::Point3D center, double radius, double height,
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

bool RayTracer::Cone::hits(const RayTracer::Ray& ray, double& t)
{
    Math::Vector3D oc = _invRot * (ray.origin - _center).toVector();
    Math::Vector3D d  = _invRot * ray.direction;
    double k  = _radius / _height;
    double k2 = k * k;
    double t_best = -1;
    Math::Vector3D N_best;

    double a = d.x*d.x + d.z*d.z - k2*d.y*d.y;
    if (std::abs(a) >= 1e-9) {
        double b = 2.0 * (oc.x*d.x + oc.z*d.z - k2*oc.y*d.y);
        double c = oc.x*oc.x + oc.z*oc.z - k2*oc.y*oc.y;
        double delta = b*b - 4.0*a*c;
        if (delta >= 0) {
            double sq = std::sqrt(delta);
            double ts[2] = {(-b - sq) / (2.0*a), (-b + sq) / (2.0*a)};
            for (double ti : ts) {
                if (ti < 1e-9) continue;
                double y = oc.y + ti * d.y;
                if (y < 0 || y > _height) continue;
                if (t_best < 0 || ti < t_best) {
                    Math::Vector3D hp(oc.x + ti*d.x, oc.y + ti*d.y, oc.z + ti*d.z);
                    t_best = ti;
                    N_best = Math::Vector3D(hp.x, -k2 * hp.y, hp.z);
                }
                break;
            }
        }
    }
    if (std::abs(d.y) > 1e-9) {
        double tc = (_height - oc.y) / d.y;
        if (tc >= 1e-9 && (t_best < 0 || tc < t_best)) {
            double px = oc.x + tc * d.x;
            double pz = oc.z + tc * d.z;
            if (px*px + pz*pz <= _radius * _radius) {
                t_best = tc;
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

Math::Vector3D RayTracer::Cone::getNormal(const Math::Point3D& hitPoint) const
{
    (void)hitPoint;
    Math::Vector3D n = _rot * _localNormal;
    n.normalize();
    return n;
}
