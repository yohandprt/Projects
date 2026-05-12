/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlSprite.hpp
*/

#pragma once

#include "ISprite.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

namespace ARCADE {
    class SdlSprite : public ARCADE::ISprite
    {
    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& _renderer;
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _surface;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _texture;
        SDL_Rect _rect;
        std::string _imagePath;
    public:
        SdlSprite(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer);
        ~SdlSprite() = default;

        std::string getImagePath() const override;
        void setImagePath(std::string imagePath) override;
        void draw() override;
    };
}