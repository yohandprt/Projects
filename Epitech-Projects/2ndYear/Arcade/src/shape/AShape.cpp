/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AShape.cpp
*/

#include "AShape.hpp"

ARCADE::AShape::AShape()
{
    this->_x = 0.0;
    this->_y = 0.0;
    this->_color = ARCADE::Color::Blue;
}

float ARCADE::AShape::getPosX() const
{
    return this->_x;
}

float ARCADE::AShape::getPosY() const
{
    return this->_y;
}

ARCADE::Color ARCADE::AShape::getColor() const
{
    return this->_color;
}

void ARCADE::AShape::setPosX(float x)
{
    this->_x = x;
}

void ARCADE::AShape::setPosY(float y)
{
    this->_y = y;
}

void ARCADE::AShape::setColor(ARCADE::Color color)
{
    this->_color = color;
}

bool ARCADE::AShape::isMouseHover()
{
    return false;
}

bool ARCADE::AShape::isClick()
{
    return false;
}