/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ArcadeSdl.hpp
*/

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <array>

#include "ADisplayModule.hpp"

#include "SdlRectangle.hpp"
#include "SdlCircle.hpp"
#include "SdlSprite.hpp"

namespace ARCADE {

    static std::map<std::string, SDL_KeyCode> sdlKeys = {
        {"z", SDLK_z},
        {"q", SDLK_q},
        {"s", SDLK_s},
        {"d", SDLK_d},
        {"m", SDLK_m},
        {"r", SDLK_r},
        {"up", SDLK_UP},
        {"down", SDLK_DOWN},
        {"left", SDLK_LEFT},
        {"right", SDLK_RIGHT},
        {"space", SDLK_SPACE},
        {"tab", SDLK_TAB},
        {"enter", SDLK_RETURN},
        {"esc", SDLK_ESCAPE}
    };

    static std::map<ARCADE::Color, std::array<std::size_t, 4>> sdlColors = {
        {ARCADE::Color::Black, {0, 0, 0, 0}},
        {ARCADE::Color::White, {255, 255, 255, 255}},
        {ARCADE::Color::Red, {255, 0, 0, 255}},
        {ARCADE::Color::Green, {0, 255, 0, 255}},
        {ARCADE::Color::Blue, {0, 0, 255, 255}},
        {ARCADE::Color::Yellow, {255, 255, 0, 255}},
    };

    class SDL2 : public ARCADE::ADisplayModule
    {
    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
        SDL_Event _event;
        bool _isOpen;
        int _maxX;
        int _maxY;
    public:
        SDL2();
        ~SDL2() = default;
        void init() override;
        void stop() override;
        bool isOpen() override;
        bool pollEvent() override;
        void close() override;
        void clear() override;
        void display() override;

        std::size_t getWindowSizeX() const override;
        std::size_t getWindowSizeY() const override;
        bool isKeyPressed(std::string key) override;
        std::string getKeyPressed() override;
        std::unique_ptr<ARCADE::IRectangle> createRectangle() override;
        std::unique_ptr<ARCADE::ICircle> createCircle() override;
        std::unique_ptr<ARCADE::IRectangle> createSprite() override;
    };

}