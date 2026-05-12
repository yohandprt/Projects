/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ACircle.hpp
*/

#pragma once

#include "ICircle.hpp"

namespace ARCADE {
    class ACircle : public ICircle
    {
    protected:
        float _d;
    public:
        ACircle();
        ~ACircle() = default;

        float getDiameter() const override;
        void setDiameter(float diameter) override;
    };
}