/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AShape.hpp
*/

#pragma once

#include "IShape.hpp"

#include <SFML/Graphics.hpp>

namespace ARCADE {
    class AShape : public IShape
    {
    protected:
        float _x;
        float _y;
        ARCADE::Color _color;
    public:
        AShape();
        ~AShape() = default;

        float getPosX() const override;
        float getPosY() const override;
        ARCADE::Color getColor() const override;

        void setPosX(float x) override;
        void setPosY(float y) override;
        void setColor(ARCADE::Color color) override;

        bool isMouseHover() override;
        bool isClick() override;
    };
}