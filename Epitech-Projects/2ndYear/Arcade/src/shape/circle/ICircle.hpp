/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ICircle.hpp
*/

#pragma once

#include "AShape.hpp"

namespace ARCADE {

    class ICircle : public AShape
    {
    public:
        virtual ~ICircle() = default;

        virtual float getDiameter() const = 0;

        virtual void setDiameter(float diameter) = 0;
    };
}