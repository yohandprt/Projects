/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplayModule.hpp
*/

#pragma once

#pragma once

#include "IDisplayModule.hpp"

namespace ARCADE {
    class ADisplayModule : public ARCADE::IDisplayModule
    {
    public:
        ADisplayModule() = default;
        ~ADisplayModule() = default;

        virtual std::size_t getWindowSizeX() const = 0;
        virtual std::size_t getWindowSizeY() const = 0;
        virtual bool isKeyPressed(std::string key) = 0;
        virtual std::string getKeyPressed() = 0;
        virtual std::unique_ptr<ARCADE::IRectangle> createRectangle() = 0;
        virtual std::unique_ptr<ARCADE::ICircle> createCircle() = 0;
        virtual std::unique_ptr<ARCADE::IRectangle> createSprite() = 0;
    };
}