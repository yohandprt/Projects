/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlSprite.cpp
*/

#include "SdlSprite.hpp"

ARCADE::SdlSprite::SdlSprite(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer)
: _renderer(renderer),
_surface(nullptr, SDL_FreeSurface),
_texture(nullptr, SDL_DestroyTexture)
{
    this->_w = 20.0;
    this->_h = 20.0;
}

std::string ARCADE::SdlSprite::getImagePath() const
{
    return this->_imagePath;
}

void ARCADE::SdlSprite::setImagePath(std::string imagePath)
{
    this->_imagePath = imagePath;

    this->_surface.reset(IMG_Load(imagePath.c_str()));
    this->_texture.reset(SDL_CreateTextureFromSurface(this->_renderer.get(), this->_surface.get()));

    this->_rect.x = this->_x;
    this->_rect.y = this->_y;
    this->_rect.w = this->_w;
    this->_rect.h = this->_h;
}

void ARCADE::SdlSprite::draw()
{
    this->_rect.x = this->_x;
    this->_rect.y = this->_y;
    this->_rect.w = this->_w;
    this->_rect.h = this->_h;

    SDL_RenderCopy(this->_renderer.get(), this->_texture.get(), NULL, &this->_rect);
}