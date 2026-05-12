/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlRectangle.cpp
*/

#include "SdlRectangle.hpp"

#include <filesystem>

ARCADE::SdlRectangle::SdlRectangle(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer)
: _renderer(renderer),
_buttonState(0),
_font(nullptr, TTF_CloseFont),
_textSurface(nullptr, SDL_FreeSurface),
_textTexture(nullptr, SDL_DestroyTexture),
_textColor(ARCADE::Color::White)
{
    this->_rectangle = {.x = this->_x, .y = this->_y, .w = this->_w, .h = this->_h};

    this->_font.reset(TTF_OpenFont("assets/fonts/font.otf", 20));

    if (!this->_font)
        printf("PAS DE FONT\n");
}

std::string ARCADE::SdlRectangle::getText() const
{
    return this->_strText;
}

ARCADE::Color ARCADE::SdlRectangle::getTextColor() const
{
    return this->_textColor;
}

void ARCADE::SdlRectangle::setText(std::string text, std::size_t charactereSize, ARCADE::Color color)
{
    (void)charactereSize;

    this->_strText = text;
    if (this->_strText.empty()) {
        this->_textSurface.reset();
        this->_textTexture.reset();
        return;
    }

    std::array<std::size_t, 4> textRgba = sdlColors.at(color);

    SDL_Color sColor = {static_cast<unsigned char>(textRgba[0]), static_cast<unsigned char>(textRgba[1]), static_cast<unsigned char>(textRgba[2]), static_cast<unsigned char>(textRgba[3])};

    this->_textSurface.reset(TTF_RenderText_Blended(this->_font.get(), text.c_str(), sColor));
    if (!this->_textSurface)
        printf("PAS DE TEXT SURFACE\n");

    this->_textTexture.reset(SDL_CreateTextureFromSurface(this->_renderer.get(), this->_textSurface.get()));
    if (!this->_textTexture)
        printf("PAS DE TEXT TEXTURE\n");

    this->_textColor = color;
}

bool ARCADE::SdlRectangle::isMouseHover()
{
    int x = 0;
    int y = 0;

    this->_buttonState = SDL_GetMouseState(&x, &y);

    if (x >= this->_x && y >= this->_y &&
        x <= (this->_x + this->_w) && y <= (this->_y + this->_h))
        return true;
    return false;
}

bool ARCADE::SdlRectangle::isClick()
{
    if (isMouseHover() && (this->_buttonState & SDL_BUTTON(SDL_BUTTON_LEFT)))
        return true;
    return false;
}

void ARCADE::SdlRectangle::draw()
{
    if (!this->_renderer)
        return;
    this->_rectangle = {.x = this->_x, .y = this->_y, .w = this->_w, .h = this->_h};
    std::array<std::size_t, 4> rectRgba = sdlColors.at(this->_color);

    SDL_SetRenderDrawColor(this->_renderer.get(), rectRgba[0], rectRgba[1], rectRgba[2], rectRgba[3]);
    SDL_RenderFillRectF(this->_renderer.get(), &this->_rectangle);

    if (this->_textSurface) {
        this->_textRect = {
            .x = static_cast<int>(this->_x + (this->_w - this->_textSurface->w) / 2),
            .y = static_cast<int>(this->_y + (this->_h - this->_textSurface->h) / 2),
            .w = this->_textSurface->w,
            .h = this->_textSurface->h
        };
        SDL_RenderCopy(this->_renderer.get(), this->_textTexture.get(), NULL, &this->_textRect);
    }
}