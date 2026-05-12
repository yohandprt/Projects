/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ARectangle.cpp
*/

#include "ARectangle.hpp"

ARCADE::ARectangle::ARectangle()
{
    this->_w = 20.0;
    this->_h = 20.0;
}

float ARCADE::ARectangle::getWidth() const
{
    return this->_w;
}

float ARCADE::ARectangle::getHeight() const
{
    return this->_h;
}

std::string ARCADE::ARectangle::getText() const
{
    return "";
}

ARCADE::Color ARCADE::ARectangle::getTextColor() const
{
    return ARCADE::Color::Blue;
}

void ARCADE::ARectangle::setWidth(float width)
{
    this->_w = width;
}

void ARCADE::ARectangle::setHeight(float height)
{
    this->_h = height;
}

void ARCADE::ARectangle::setText(std::string text, std::size_t charactereSize, ARCADE::Color color)
{
    (void)text;
    (void)charactereSize;
    (void)color;
}