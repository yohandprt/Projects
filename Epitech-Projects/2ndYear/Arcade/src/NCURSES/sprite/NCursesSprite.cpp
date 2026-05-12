/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesSprite.cpp
*/

#include "NCursesSprite.hpp"

ARCADE::NCursesSprite::NCursesSprite()
{
    this->_rectMaker = std::make_unique<ARCADE::NCursesRectangle>();
    this->_rectMaker->setColor(ARCADE::Color::White);
}

std::string ARCADE::NCursesSprite::getImagePath() const
{
    return this->_imagePath;
}

void ARCADE::NCursesSprite::setImagePath(std::string imagePath)
{
    this->_imagePath = imagePath;
}

void ARCADE::NCursesSprite::draw()
{
    this->_rectMaker->setPosX(this->_x);
    this->_rectMaker->setPosY(this->_y);
    this->_rectMaker->setWidth(this->_w);
    this->_rectMaker->setHeight(this->_h);
    this->_rectMaker->draw();
}