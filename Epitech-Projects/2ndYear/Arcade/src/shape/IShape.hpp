/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IShape.hpp
*/

#pragma once

#include <iostream>

namespace ARCADE {

    enum Color {
        Black,
        White,
        Red,
        Green,
        Blue,
        Yellow,
    };

    class IShape
    {
    public:
        virtual ~IShape() = default;

        virtual float getPosX() const = 0;
        virtual float getPosY() const = 0;
        virtual ARCADE::Color getColor() const = 0;

        virtual void setPosX(float x) = 0;
        virtual void setPosY(float y) = 0;
        virtual void setColor(ARCADE::Color color) = 0;

        virtual bool isMouseHover() = 0;
        virtual bool isClick() = 0;

        virtual void draw() = 0;
    };
    

}