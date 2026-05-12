/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Rectangle.hpp
*/

#pragma once

#include <iostream>

#include "AShape.hpp"

namespace ARCADE {

    class IRectangle : public AShape
    {
    public:
        virtual ~IRectangle() = default;

        virtual float getWidth() const = 0;
        virtual float getHeight() const = 0;
        virtual std::string getText() const = 0;
        virtual ARCADE::Color getTextColor() const = 0;

        virtual void setWidth(float width) = 0;
        virtual void setHeight(float height) = 0;
        virtual void setText(std::string text, std::size_t charactereSize, ARCADE::Color color) = 0;
    };
}