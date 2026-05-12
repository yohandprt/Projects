/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlCircle.cpp
*/

#include "SdlCircle.hpp"
#include <cmath>

ARCADE::SdlCircle::SdlCircle(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer) : _renderer(renderer)
{
}

void ARCADE::SdlCircle::draw()
{
    if (!this->_renderer)
        return;

    std::array<std::size_t, 4> circleRgba = sdlColors.at(this->_color);
    SDL_SetRenderDrawColor(this->_renderer.get(), circleRgba[0], circleRgba[1], circleRgba[2], circleRgba[3]);

    float radius = this->_d / 2.0f;
    float centerX = this->_x + radius;

    for (float i = 0; i < this->_d; i++) {
        float dy = i - radius;
        float h2 = radius * radius - dy * dy;
        if (h2 >= 0) {
            float dx = std::sqrt(h2);
            SDL_RenderDrawLineF(this->_renderer.get(), centerX - dx, this->_y + i, centerX + dx, this->_y + i);
        }
    }
}