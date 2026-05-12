/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ACircle.cpp
*/

#include "ACircle.hpp"

ARCADE::ACircle::ACircle()
{
    this->_d = 40.0;
}

float ARCADE::ACircle::getDiameter() const
{
    return this->_d;
}
void ARCADE::ACircle::setDiameter(float diameter)
{
    this->_d = diameter;
}