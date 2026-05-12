/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SfmlSprite.cpp
*/

#include "SfmlSprite.hpp"

ARCADE::SfmlSprite::SfmlSprite(sf::RenderWindow &window) : _window(window)
{
    this->_w = 20.0;
    this->_h = 20.0;
    // this->_imagePath = "";
}

std::string ARCADE::SfmlSprite::getImagePath() const
{
    return this->_imagePath;
}

void ARCADE::SfmlSprite::setImagePath(std::string imagePath)
{
    this->_imagePath = imagePath;
    this->_texture.loadFromFile(this->_imagePath);
    this->_sprite.setTexture(this->_texture);
    this->_textureSize = this->_texture.getSize();
}

void ARCADE::SfmlSprite::draw()
{
    this->_sprite.setPosition(this->_x, this->_y);
    this->_sprite.setScale(this->_w / this->_textureSize.x, this->_h / this->_textureSize.y);

    this->_window.draw(this->_sprite);
}