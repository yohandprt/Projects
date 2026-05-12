/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlRectangle.hpp
*/

#pragma once

#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ARectangle.hpp"
#include "ArcadeSdl.hpp"

namespace ARCADE {
    class SdlRectangle : public ARectangle
    {
    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& _renderer;
        SDL_FRect _rectangle;
        Uint32 _buttonState;
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font;
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _textSurface;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _textTexture;
        SDL_Rect _textRect;
        std::string _strText;
        ARCADE::Color _textColor;
    public:
        SdlRectangle(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer);
        ~SdlRectangle() = default;

        std::string getText() const override;
        ARCADE::Color getTextColor() const override;
        void setText(std::string text, std::size_t charactereSize, ARCADE::Color color) override;

        bool isMouseHover() override;
        bool isClick() override;

        void draw() override;
    };
}