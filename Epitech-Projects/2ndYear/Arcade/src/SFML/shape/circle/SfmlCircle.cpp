/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SfmlCircle.cpp
*/

#include "SfmlCircle.hpp"

ARCADE::SfmlCircle::SfmlCircle(sf::RenderWindow &window) : _window(window)
{
    this->_circle = sf::CircleShape();

    this->_circle.setPosition(sf::Vector2f(this->_x, this->_y));
    this->_circle.setRadius(this->_d / 2);
    this->_circle.setFillColor(ARCADE::sfmlColors.at(this->_color));
}

void ARCADE::SfmlCircle::draw()
{
    this->_circle.setPosition(sf::Vector2f(this->_x, this->_y));
    this->_circle.setRadius(this->_d / 2);
    this->_circle.setFillColor(ARCADE::sfmlColors.at(this->_color));

    this->_window.draw(this->_circle);
}