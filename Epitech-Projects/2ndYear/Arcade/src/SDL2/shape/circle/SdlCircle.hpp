/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SdlCircle.hpp
*/

#pragma once

#include <SDL2/SDL.h>

#include "ACircle.hpp"
#include "ArcadeSdl.hpp"

namespace ARCADE {
    class SdlCircle : public ACircle
    {
    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& _renderer;
        SDL_FRect _circle;
    public:
        SdlCircle(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer);
        ~SdlCircle() = default;

        void draw() override;
    };
}