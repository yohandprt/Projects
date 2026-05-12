/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Core
*/

#include "Core.hpp"

RayTracer::Core::Core()
{
    _parser = std::make_unique<RayTracer::Parser>();
    _camera = nullptr;
    _primitives.clear();
    _lights.clear();
}

void RayTracer::Core::init(const int ac, const char** av)
{
    // parsing
    try {
        _parser->parse(ac, av);
        _fileHandler = _parser->parseFileHandler();
        _camera = _parser->parseCamera();
        _primitives = _parser->parseShapes();
        _lights = _parser->parseLights();
    } catch (const RayTracer::Parser::Error& e) {
        std::cerr << "Parser error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    // inits
    _render = std::make_unique<RayTracer::Display>
        (_camera->resolutionX, _camera->resolutionY, "RayTracer");
    _fileHandler->init(_camera->resolutionX, _camera->resolutionY);
}

std::size_t RayTracer::Core::getClosestPixel(const RayTracer::Ray& r, std::size_t idxCurrentPrim)
{
    this->_closestT = std::numeric_limits<double>::infinity();
    std::size_t idx = std::string::npos;

    for (std::size_t k = 0; k < _primitives.size(); k++)
    {
        if (k == idxCurrentPrim)
            continue;

        double t = 0.0;
        if (_primitives[k]->hits(r, t) && t < this->_closestT)
        {
            this->_closestT = t;
            idx = k;
        }
    }
    return idx;
}

RayTracer::Color RayTracer::Core::traceRay(const Ray& r, std::size_t depth, std::size_t idxCurrentPrim)
{
    if (depth >= MAX_NB_RAY)
        return {0, 0, 0};

    std::size_t idx = this->getClosestPixel(r, idxCurrentPrim);

    if (idx == std::string::npos)
        return this->_camera->bgColor;

    Math::Point3D hitPoint = r.origin + this->_closestT * r.direction;

    RayTracer::Color currentColor = this->_primitives[idx]->calculatePixelColor(hitPoint, r, this->_lights, this->_primitives);

    double reflectivity = this->_primitives[idx]->getMaterial()->getReflectivity();
    double transparency = this->_primitives[idx]->getMaterial()->getTransparency();

    if (reflectivity <= 0.0 && transparency <= 0.0)
        return currentColor;

    Math::Vector3D I = r.direction;
    Math::Vector3D N = this->_primitives[idx]->getNormal(hitPoint);
    I.normalize();
    N.normalize();
    N = dot(I, N) < 0 ? -1 * N : N;

    RayTracer::Color reflectedColor(0, 0, 0);
    RayTracer::Color transparentColor(0, 0, 0);

    if (reflectivity > 0.0) {
        Math::Vector3D R = I - 2.0 * dot(I, N) * N;
        R.normalize();

        RayTracer::Ray reflectedRay;
        reflectedRay.origin = hitPoint + 0.0001 * R;
        reflectedRay.direction = R;

        reflectedColor = this->traceRay(reflectedRay, depth + 1, idx);
    }

    if (transparency > 0.0) {
        RayTracer::Ray transparentRay;
        transparentRay.origin = hitPoint + 0.0001 * N;
        transparentRay.direction = I;

        transparentColor = this->traceRay(transparentRay, depth + 1, idx);
    }

    return currentColor + reflectedColor * reflectivity + transparentColor * transparency;
}

RayTracer::Color RayTracer::Core::getPixelColor(std::size_t x, std::size_t y)
{
    RayTracer::Ray r = _camera->ray(x, y);
    return this->traceRay(r, 0, -1);
}

void RayTracer::Core::run()
{
    RayTracer::Color color = _camera->bgColor;

    for (std::size_t y = 0; y < _camera->resolutionY; y++) {
        for (std::size_t x = 0; x < _camera->resolutionX; x++) {
            color = _camera->bgColor;

            color = getPixelColor(x, y);
            _fileHandler->writeColor(color);
            _render->setPixel(x, y, color);
        }
        _render->update(y);
    }
}